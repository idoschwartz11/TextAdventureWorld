#include "Player.h"
#include "Direction.h"
#include <cctype>
#include <iostream>
#include <conio.h> // For _getch in shop
#include "game.h"

using std::tolower;
using std::cout; 

static Direction oppositeDirection(Direction d) {
    switch (d) {
    case Direction::UP:    return Direction::DOWN;
    case Direction::DOWN:  return Direction::UP;
    case Direction::LEFT:  return Direction::RIGHT;
    case Direction::RIGHT: return Direction::LEFT;
    default:               return Direction::STAY;
    }
}

static constexpr int SPRING_RESTORE_DELAY_TICKS = 10;

// ctor with explicit start position
Player::Player(const Point& p, char c, int startX, int startY,
    const char movKeys[], Screen& scr)
    : screen(scr)
{
    body = p;
    ch = c;
    x = startX;
    y = startY;
    std::memcpy(keys, movKeys, NUM_KEYS + 1);
}

// ctor from point
Player::Player(const Point& p, char c, const char movKeys[], Screen& scr)
    : screen(scr)
{
    body = p;
    ch = c;
    std::memcpy(keys, movKeys, NUM_KEYS + 1);
    x = body.getX();
    y = body.getY();
}

void Player::draw() {
    // Merged: Using User 1's Color logic
    Color playerColor = screen.get_player_color(ch);
    screen.set_text_color(playerColor);

    // Using direct draw or body.draw - sticking to body.draw for consistency with Point class
    body = Point(x, y, ch);
    body.draw();

    screen.set_text_color(Color::WHITE);
}

// find the direction from the spring line towards the wall
Direction Player::findWallDirForSpring(const Point& springPos) const {
    Direction dirs[4] = {
        Direction::UP,
        Direction::DOWN,
        Direction::LEFT,
        Direction::RIGHT
    };

    for (int i = 0; i < 4; ++i) {
        Direction d = dirs[i];
        int dx = 0, dy = 0;
        switch (d) {
        case Direction::UP:    dy = -1; break;
        case Direction::DOWN:  dy = 1; break;
        case Direction::LEFT:  dx = -1; break;
        case Direction::RIGHT: dx = 1; break;
        default: break;
        }

        int cx = springPos.getX();
        int cy = springPos.getY();

        while (true) {
            cx += dx;
            cy += dy;
            if (cx < 0 || cx >= Screen::MAX_X || cy < 0 || cy >= Screen::MAX_Y)
                break;

            Point p(cx, cy, springPos.getX(), springPos.getY(), '#'); // dummy
            char c = screen.getCharAt(p);
            if (c == '#') {
                continue;
            }
            else if (c == 'W') {
                return d; // wall in direction d
            }
            else {
                break;
            }
        }
    }

    return Direction::STAY;
}

void Player::dropItem() {
    if (item == ' ')
        return;

    int cx = body.getX();
    int cy = body.getY();
    Point currPos(cx, cy, ch);

    char cell = screen.getCharAt(currPos);
    if (cell != ' ')
        return;
    
    // Bomb drop logic
    if (item == '@') {
        screen.activateBomb(cx, cy);

        item = ' ';
        if (ch == '$') screen.setP1Inventory(' ');
        else if (ch == '&') screen.setP2Inventory(' ');

        body.draw();
        return;
    }
    else {
        screen.setCharAt(cx, cy, item);
        item = ' ';

        if (ch == '$') screen.setP1Inventory(' ');
        else if (ch == '&') screen.setP2Inventory(' ');
    }

    body.draw(); // Redraw player
}

void Player::startSpringLaunch() {
    if (compressedCount <= 0 || compressDir == Direction::STAY)
        return;

    inSpringCompress = false;
    inSpringLaunch = true;

    springDir = oppositeDirection(compressDir);
    springSpeed = compressedCount;
    springTicksLeft = compressedCount * compressedCount;

    body.setDirection(springDir);

    if (numCollapsedSpringCells > 0) {
        restoringSpring = true;
        restoreIndex = 0;
        restoreDelayCounter = SPRING_RESTORE_DELAY_TICKS;
    }
}

void Player::springRestoreTick() {
    if (!restoringSpring)
        return;

    if (restoreDelayCounter > 0) {
        --restoreDelayCounter;
        return;
    }

    if (restoreIndex < numCollapsedSpringCells) {
        Point& p = collapsedSpringCells[numCollapsedSpringCells - 1 - restoreIndex];
        screen.setCharAt(p.getX(), p.getY(), '#');
        ++restoreIndex;
        restoreDelayCounter = SPRING_RESTORE_DELAY_TICKS;
    }

    if (restoreIndex >= numCollapsedSpringCells) {
        restoringSpring = false;
        numCollapsedSpringCells = 0;
        restoreIndex = 0;
        restoreDelayCounter = 0;
    }
}
    

void Player::handleKeyPressed(char key) {
    char lower = tolower(key);

    // item drop
    if ((ch == '$' && lower == 'e') ||
        (ch == '&' && lower == 'o')) {
        dropItem();
        return;
    }

    // while under spring launch effect: stay and direction changes are ignored 
    if (inSpringLaunch) {
        if (lower == tolower(keys[4])) {
            return;
        }
        return;
    }

    // while compressed against spring near the wall:
    if (inSpringCompress) {
        bool isMyKey = false;
        for (int i = 0; i < NUM_KEYS; ++i) {
            if (lower == tolower(keys[i])) {
                isMyKey = true;
                break;
            }
        }

        if (isMyKey) {
            // any move releases the spring
            startSpringLaunch();
        }
        return;
    }

    Direction newDir = Direction::STAY;
    bool hasDir = false;

    if (lower == tolower(keys[0])) {
        newDir = Direction::UP; hasDir = true;
    }
    else if (lower == tolower(keys[1])) {
        newDir = Direction::LEFT; hasDir = true;
    }
    else if (lower == tolower(keys[2])) {
        newDir = Direction::RIGHT; hasDir = true;
    }
    else if (lower == tolower(keys[3])) {
        newDir = Direction::DOWN; hasDir = true;
    }
    else if (lower == tolower(keys[4])) {
        newDir = Direction::STAY; hasDir = true;
    }

    if (hasDir) {
        body.setDirection(newDir);
    }
}

void Player::move() {
    springRestoreTick();
    if (x < 0 || y < 0) { 
        return;
    }
   
    // --- Spring Launch Movement ---
    if (inSpringLaunch) {
        if (springTicksLeft <= 0 || springSpeed <= 0 || springDir == Direction::STAY) {
            inSpringLaunch = false;
            springSpeed = 0;
            springTicksLeft = 0;
            body.setDirection(Direction::STAY);
            return;
        }

        int currX = body.getX();
        int currY = body.getY();
        Point currPos(currX, currY, ch);
        char under = screen.getCharAt(currPos);

        int dirX = 0, dirY = 0;
        switch (springDir) {
        case Direction::UP:    dirY = -1; break;
        case Direction::DOWN:  dirY = 1;  break;
        case Direction::LEFT:  dirX = -1; break;
        case Direction::RIGHT: dirX = 1;  break;
        default: break;
        }

        int finalX = currX;
        int finalY = currY;
        bool blocked = false;

        for (int step = 0; step < springSpeed; ++step) {

            int nextX = (finalX + dirX + Screen::MAX_X) % Screen::MAX_X;
            int nextY = (finalY + dirY + Screen::MAX_Y) % Screen::MAX_Y;

            if (screen.isHudCell(nextX, nextY)) {
                blocked = true;
                break;
            }

            Point stepPos(nextX, nextY, ch);

            if (screen.isWall(stepPos)) {
                blocked = true;
                break;
            }

            if (other != nullptr && nextX == other->getX() && nextY == other->getY()) {
                blocked = true;
                break;
            }

            // Merged: Keep User 1's superior obstacle pushing with spring bonus
            game* g = screen.getGame();
            if (g && g->isObstacleAt(nextX, nextY)) {
                int bonus = compressedCount;
                bool pushed = false;
                if (other != nullptr) {
                    pushed = g->tryPushObstacle(screen, *this, *other, springDir, bonus);
                }
                if (!pushed) {
                    blocked = true;
                    break;
                }
            }

            char cell = screen.getCharAt(stepPos);

            // Merged: Using User 2's coin logic (individual wallets) for Shop compatibility
            if (cell == 'o') {
                ++coins;
                screen.setCharAt(nextX, nextY, ' ');
                if (ch == '$') screen.setP1Coins(coins);
                else if (ch == '&') screen.setP2Coins(coins);
            }
            else if ((cell == '!' || cell == 'K' || cell == '@') && item == ' ') {
                item = cell;
                screen.setCharAt(nextX, nextY, ' ');
                if (ch == '$') screen.setP1Inventory(item);
                else if (ch == '&') screen.setP2Inventory(item);
            }

            finalX = nextX;
            finalY = nextY;
        }

        gotoxy(currX, currY);
        cout << under;

        body.set(finalX, finalY);
        x = finalX;
        y = finalY;
        draw(); // Use local draw for color support

        if (ch == '$')
            screen.setP1Position(x, y);
        else if (ch == '&')
            screen.setP2Position(x, y);

        --springTicksLeft;

        if (springTicksLeft <= 0 || blocked) {
            inSpringLaunch = false;
            springSpeed = 0;
            springTicksLeft = 0;
            body.setDirection(Direction::STAY);
        }

        return;
    }

    // while compressed we do not move automatically, only wait for key
    if (inSpringCompress) {
        return;
    }

    // --- Normal Movement ---
    if (body.getDiffX() == 0 && body.getDiffY() == 0) {
        return;
    }

    int currX = body.getX();
    int currY = body.getY();
    Point currPos(currX, currY, ch);
    char under = screen.getCharAt(currPos);

    int nextX = (currX + body.getDiffX() + Screen::MAX_X) % Screen::MAX_X;
    int nextY = (currY + body.getDiffY() + Screen::MAX_Y) % Screen::MAX_Y;
    Point nextPos(nextX, nextY, ch);

    // wall
    if (screen.isWall(nextPos)) {
        body.setDirection(Direction::STAY);
        return;
    }

    // other player
    if (other != nullptr && nextX == other->getX() && nextY == other->getY()) {
        body.setDirection(Direction::STAY);
        other->body.setDirection(Direction::STAY);
        return;
    }

    // obstacle (not in screen map, drawn by game overlay) - User 1 logic
    if (screen.getGame() != nullptr && screen.getGame()->isObstacleAt(nextX, nextY)) {
        Direction dir = Direction::STAY;
        int dx = body.getDiffX();
        int dy = body.getDiffY();

        if (dx == 1 && dy == 0) dir = Direction::RIGHT;
        else if (dx == -1 && dy == 0) dir = Direction::LEFT;
        else if (dx == 0 && dy == -1) dir = Direction::UP;
        else if (dx == 0 && dy == 1) dir = Direction::DOWN;

        bool pushed = false;
        if (other != nullptr && dir != Direction::STAY) {
            pushed = screen.getGame()->tryPushObstacle(screen, *this, *other, dir);
        }

        if (!pushed) {
            return;
        }
    }

    char cell = screen.getCharAt(nextPos);

    // --- MERGED FEATURES FROM USER 2 (Shop, Riddles, Slopes) ---

    // 1. Shop Check
    if (screen.is_shop_item(cell)) {
        if (tryToBuyItem(nextX, nextY)) {
            return; // If interaction happened, don't move onto the item
        }
    }

    // 2. Riddle Check
    if (cell == 'R') {
        bool solved = screen.triggerRiddle();
        if (solved) {
            screen.setCharAt(nextX, nextY, ' ');
            // Move into the riddle spot after solving
            gotoxy(currX, currY);
            cout << under;
            body.set(nextX, nextY);
            x = nextX;
            y = nextY;
            draw();
            if (ch == '$') screen.setP1Position(x, y);
            else if (ch == '&') screen.setP2Position(x, y);
        }
        else {
            body.setDirection(Direction::STAY);
        }
        return;
    }

    // 3. Slopes
    if (cell == '\\' || cell == '/') {
        char newState = (cell == '\\') ? '/' : '\\';
        screen.setCharAt(nextX, nextY, newState);
        cell = newState;
    }

    // --- Spring Compression (User 1 Logic) ---
    if (cell == '#') {
        if (restoringSpring) {
            bool sameSpringCell = false;
            for (int i = 0; i < numCollapsedSpringCells; ++i) {
                if (collapsedSpringCells[i].getX() == nextX &&
                    collapsedSpringCells[i].getY() == nextY) {
                    sameSpringCell = true;
                    break;
                }
            }
            if (!sameSpringCell) {
                // Clean up previous spring restoration instantly if entering a new one
                for (int i = 0; i < numCollapsedSpringCells; ++i) {
                    Point& p = collapsedSpringCells[i];
                    screen.setCharAt(p.getX(), p.getY(), '#');
                }
                restoringSpring = false;
                numCollapsedSpringCells = 0;
                restoreIndex = 0;
                restoreDelayCounter = 0;
            }
        }

        // Logic to find wall and compress
        if (!restoringSpring) {
            Direction wallDir = findWallDirForSpring(nextPos);
            if (wallDir != Direction::STAY) {
                int dx = 0, dy = 0;
                switch (wallDir) {
                case Direction::UP:    dy = -1; break;
                case Direction::DOWN:  dy = 1; break;
                case Direction::LEFT:  dx = -1; break;
                case Direction::RIGHT: dx = 1; break;
                default: break;
                }

                int sx = nextPos.getX();
                int sy = nextPos.getY();
                int odx = -dx;
                int ody = -dy;

                // Find start of spring
                while (true) {
                    int nx = sx + odx;
                    int ny = sy + ody;
                    if (nx < 0 || nx >= Screen::MAX_X || ny < 0 || ny >= Screen::MAX_Y) break;
                    Point p(nx, ny, ch);
                    if (!screen.isSpring(p)) break;
                    sx = nx;
                    sy = ny;
                }

                numCollapsedSpringCells = 0;
                compressedCount = 0;

                int cx2 = sx;
                int cy2 = sy;
                Point p2(cx2, cy2, ch);

                while (screen.isSpring(p2) && numCollapsedSpringCells < MAX_SPRING_LEN) {
                    collapsedSpringCells[numCollapsedSpringCells] = p2;
                    ++numCollapsedSpringCells;
                    ++compressedCount;

                    screen.setCharAt(cx2, cy2, ' ');

                    cx2 += dx;
                    cy2 += dy;
                    p2 = Point(cx2, cy2, ch);
                }

                int wallNeighborX = cx2 - dx;
                int wallNeighborY = cy2 - dy;

                gotoxy(currX, currY);
                cout << under;

                body.set(wallNeighborX, wallNeighborY);
                x = wallNeighborX;
                y = wallNeighborY;
                draw();

                if (ch == '$') screen.setP1Position(x, y);
                else if (ch == '&') screen.setP2Position(x, y);

                inSpringCompress = true;
                compressDir = wallDir;
                body.setDirection(Direction::STAY);

                return;
            }
        }
    }

    // --- Items (Coins/Keys/Bombs) - User 2 logic for individual wallets ---
    if (cell == 'o') {
        ++coins;
        screen.setCharAt(nextX, nextY, ' ');
        if (ch == '$') screen.setP1Coins(coins);
        else if (ch == '&') screen.setP2Coins(coins);
    }
    else if (cell == '!' || cell == 'K' || cell == '@') {
        if (item == ' ') {
            item = cell;
            screen.setCharAt(nextX, nextY, ' ');
            if (ch == '$') screen.setP1Inventory(item);
            else if (ch == '&') screen.setP2Inventory(item);
        }
    }

    // --- Doors (User 2 logic for specific door IDs) ---
    if (cell == '1' || cell == '2' || cell == '9') {
        // If it's the exit door (9) or other player is ready
        if (cell == '9' || screen.isOtherPlayerReady(ch)) {
            gotoxy(currX, currY);
            cout << under;
            x = -1;
            y = -1;
            body.set(-1, -1);
            screen.playerReadyToTransition(ch, cell); // Pass cell ID
            return;
        }
        if (item == 'K') {
            // User 2: setDoorUnlocked logic could be added here if implemented in screen
            // For now, we consume key and wait
            item = ' ';
            if (ch == '$') screen.setP1Inventory(' ');
            else if (ch == '&') screen.setP2Inventory(' ');
            
            gotoxy(currX, currY);
            cout << under;
            x = -1;
            y = -1;
            body.set(-1, -1);
            screen.playerReadyToTransition(ch, cell); // Pass cell ID
            return;
        }
        else {
            // no key
            body.setDirection(Direction::STAY);
            return;
        }
    }

    gotoxy(currX, currY);
    cout << under;

    body.move();
    x = body.getX();
    y = body.getY();
    draw();

    if (ch == '$')
        screen.setP1Position(x, y);
    else if (ch == '&')
        screen.setP2Position(x, y);

}

void Player::resetPosition(int newX, int newY) {
    x = newX;
    y = newY;
    body.set(newX, newY);
    body.setDirection(Direction::STAY); // Ensure they start still
    inSpringCompress = false; 
    inSpringLaunch = false;
}

void Player::takeDamage(int dmg) {
    if (dmg <= 0)
        return;

    hearts -= dmg;
    if (hearts < 0)
        hearts = 0;

    if (ch == '$')
        screen.setP1Hearts(hearts);
    else if (ch == '&')
        screen.setP2Hearts(hearts);
}

// --- Merged: Shop Logic from User 2 ---
bool Player::tryToBuyItem(int itemX, int itemY) {
    Point itemPos(itemX, itemY, ' ');
    char itemChar = screen.getCharAt(itemPos);

    int price = 0;
    if (itemChar == 'K') {
        price = 8;
    }
    else if (itemChar == '!' || itemChar == 'H' || itemChar == '?') {
        price = 5;
    }
    else {
        return false;
    }

    Point pricePos(itemX, itemY + 1, ' ');
    char priceTagChar = screen.getCharAt(pricePos);

    if (priceTagChar != ('0' + price)) {
        return false; 
    }

    if (coins < price) {
        return false;
    }

    if (itemChar == '?') {
        coins -= price;
        if (ch == '$') screen.setP1Coins(coins);
        else if (ch == '&') screen.setP2Coins(coins);
        
        screen.setCharAt(itemX, itemY, ' ');
        screen.setCharAt(itemX, itemY + 1, ' ');
        
        std::string clue = screen.getGameClue();
        screen.displayMessage(clue);

        gotoxy(10, 17);
        std::cout << "Press any key to continue...";
        _getch(); // Blocking wait for user acknowledgement
        gotoxy(2, 23);
        std::cout << "                                                      ";
        return true;
    }

    bool hasRoom = false;

    if (itemChar == 'H' && hearts < 9) {
        hasRoom = true;
    }
    else if ((itemChar == '!' || itemChar == 'K') && item == ' ') {
        hasRoom = true;
    }

    if (!hasRoom) {
        return false;
    }

    coins -= price;
    if (ch == '$') screen.setP1Coins(coins);
    else if (ch == '&') screen.setP2Coins(coins);

    if (itemChar == 'H') {
        hearts++;
        if (ch == '$') screen.setP1Hearts(hearts);
        else if (ch == '&') screen.setP2Hearts(hearts);
    }
    else {
        item = itemChar;
        if (ch == '$') screen.setP1Inventory(item);
        else if (ch == '&') screen.setP2Inventory(item);
    }

    screen.setCharAt(itemX, itemY, ' ');
    screen.setCharAt(itemX, itemY + 1, ' ');

    return true;
}