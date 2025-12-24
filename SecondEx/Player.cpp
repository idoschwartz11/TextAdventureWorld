#include "Player.h"
#include "Direction.h"
#include <cctype>
#include <iostream>
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
    Color playerColor = screen.get_player_color(ch);
    screen.set_text_color(playerColor);

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
    
	//ido, that's for bomb drop
    if (item == '@') {
        screen.activateBomb(cx, cy);

        item = ' ';

        if (ch == '$')
            screen.setP1Inventory(' ');
        else if (ch == '&')
            screen.setP2Inventory(' ');

        body.draw();
        return;
    }
    else {
        screen.setCharAt(cx, cy, item);
        item = ' ';

        if (ch == '$')
            screen.setP1Inventory(' ');
        else if (ch == '&')
            screen.setP2Inventory(' ');
    }

    body.draw();
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
    // stay does nothing, any move key releases
    if (inSpringCompress) {
        bool isMyKey = false;
        for (int i = 0; i < NUM_KEYS; ++i) {
            if (lower == tolower(keys[i])) {
                isMyKey = true;
                break;
            }
        }

        if (isMyKey) {
            // any of this player's movement keys (up/left/right/down/stay) releases the spring
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
   
    // spring launch movement
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

            int nextX = finalX + dirX;
            int nextY = finalY + dirY;

            if (nextX < 0 || nextX >= Screen::MAX_X ||
                nextY < 0 || nextY >= Screen::MAX_Y) {
                blocked = true;
                break;
            }

            if (screen.isHudCell(nextX, nextY)) {
                blocked = true;
                break;
            }

            Point stepPos(nextX, nextY, ch);

            if (screen.isWall(stepPos)) {
                blocked = true;
                break;
            }

            if (other != nullptr &&
                nextX == other->getX() &&
                nextY == other->getY()) {
                blocked = true;
                break;
            }

            game* g = screen.getGame();
            if (g && g->isObstacleAt(nextX, nextY)) {

                int bonus = compressedCount;

                bool pushed = false;
                if (other != nullptr) {
                    pushed = g->tryPushObstacle(
                        screen,
                        *this,
                        *other,
                        springDir,
                        bonus
                    );
                }

                if (!pushed) {
                    blocked = true;
                    break;
                }
            }

            char cell = screen.getCharAt(stepPos);

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
        body.draw();

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

    // normal movement
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

    // obstacle (not in screen map, drawn by game overlay)
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

    // spring: snap to wall side and fully compress
        // spring: snap to wall side and fully compress
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

            if (sameSpringCell) {
				//the spring cell is still restoring, do nothing
            }
            else {
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

        bool sameSpringCell = false;
        if (restoringSpring) {
            for (int i = 0; i < numCollapsedSpringCells; ++i) {
                if (collapsedSpringCells[i].getX() == nextX &&
                    collapsedSpringCells[i].getY() == nextY) {
                    sameSpringCell = true;
                    break;
                }
            }
        }

        if (sameSpringCell) {
            //do nothing
        }
        else {
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
                while (true) {
                    int nx = sx + odx;
                    int ny = sy + ody;
                    if (nx < 0 || nx >= Screen::MAX_X || ny < 0 || ny >= Screen::MAX_Y)
                        break;
                    Point p(nx, ny, ch);
                    if (!screen.isSpring(p))
                        break;
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
                body.draw();

                if (ch == '$')
                    screen.setP1Position(x, y);
                else if (ch == '&')
                    screen.setP2Position(x, y);

                inSpringCompress = true;
                compressDir = wallDir;
                body.setDirection(Direction::STAY);

                return;
            }
        }
    }
    if (cell == 'o') {
        ++coins;
        screen.setCharAt(nextX, nextY, ' ');
        if (ch == '$')
            screen.setP1Coins(coins);
        else if (ch == '&')
            screen.setP2Coins(coins);
    }
    else if (cell == '!' || cell == 'K' || cell == '@') {
        if (item == ' ') {
            item = cell;
            screen.setCharAt(nextX, nextY, ' ');
            if (ch == '$')
                screen.setP1Inventory(item);
            else if (ch == '&')
                screen.setP2Inventory(item);
        }
    }
    // door
    if (cell == '1' || cell == '2' || cell == '9') {
        if (cell == '9' || screen.isOtherPlayerReady(ch)) {
            gotoxy(currX, currY);
            cout << under;

            x = -1;
            y = -1;
            body.set(-1, -1);

            screen.playerReadyToTransition(ch);
            return;
        }
        if (item == 'K') {
            //screen.setCharAt(nextX, nextY, ' ');
            item = ' ';
            if (ch == '$')
                screen.setP1Inventory(' ');
            else if (ch == '&')
                screen.setP2Inventory(' ');
            gotoxy(currX, currY);
            cout << under;

            x = -1;
            y = -1;
            body.set(-1, -1);

            screen.playerReadyToTransition(ch);
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
    body.draw();

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
