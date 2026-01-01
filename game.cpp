#include <iostream>
#include <conio.h>
#include <windows.h>
#include "game.h"
#include "Screen.h"
#include "utils.h"
#include "Player.h"
#include <stack>
#include <vector>
#include <io.h>
#include <algorithm>
#include "Obstacle.h"
#include <sstream>
#include <iomanip>

enum Keys { ESC = 27 };


static std::string makeWorldFileName(int idx)
{
    std::ostringstream os;
    os << "adv-world_" << std::setw(2) << std::setfill('0') << idx << ".screen";
    return os.str();
}

// --- Maps (Merged Collection from both users for fallback) ---

// ROOM 0 (Spawn) - Using User 1's version mostly but ensuring it aligns with Ex2 requirements
const std::string MAP_ROOM_0[Screen::MAX_Y] = {
   //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W    #    WWWWWWWWWWWWWWWW  #    o     o            W              WKW|  P.I : |", // 1
    "W         W            o  W #                @      W              WWW| <3 x3  |", // 2
    "W   o     W   WWWWWWW     W # WWWWW WWWWW         WWW   WWWWWWWWW    W|  o x00 |", // 3
    "W         W * W     W     W   W       o W   o     W o   Woo     W    W|        |", // 4
    "W   WWWWWWW * W ooo W  o  W * W  o      W         W     Woo     W    W| Inv:   |", // 5
    "W   W     W * W ooo W     W * W      o  WWWWWWWWWWW  o  WWWWWWWWW    W|        |", // 6
    "W o W     W   W ooo W     W   W   o      o      o          o         W|        |", // 7
    "W   W     W   W     W     W   W           WWWWWWWWWWWWW            o W|  X=00  |", // 8
    "W   W     W   WWWWWWW  o  W   WWWWWWWW o  W          o W             W|  Y=00  |", // 9
    "W  * W   o        W         o   W|        |", // 10
    "W        ** WWWWWWWWWWWWWW      @      W      @     WWWWWWWWWWWWWWW|--------|", // 11
    "W#### ** W            W             W o        o W   W       W1W|  P.II: |", // 12
    "W   WWWWWWWW   W   o        W   WWWWWWWWWWW          WWW   W   o   WWW| <3 x3  |", // 13
    "W   W      W   W       o    W   W          o   o        o  W        oW|  o x00 |", // 14
    "W o W  o   W   W                W   o   o                 WWWWWW     W|        |", // 15
    "W   W      W   WWWWWWWWWWWWWW   WWWWWWWWWWWWWWWWWWWWWWWWWWW    W    oW| Inv:   |", // 16
    "W   WWWWWWWW                 o                o           W    W     W|        |", // 17
    "W                o      o           o      o       o      W o  W     W|        |", // 18
    "W   o          WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W     W|  X=00  |", // 19
    "W         o    W                     o         o           WWWWWWWWWWW|  Y=00  |", // 20
    "W   o          W   o             o                    o              W|        |", // 21
    "W         o    W         o                  o      o                 W|        |", // 22
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWMWWWWWWWWW|        |", // 23
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// ROOM 9 (Shop/Secret) - User 2's design
const std::string MAP_ROOM_9[Screen::MAX_Y] = {
//01234567890123456789012345678901234567890123456789012345678901234567890123456789
 "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
 "W 9                                                                  W|  P.I : |", // 1
 "W                                                                    W| <3 x3  |", // 2
 "W                                                                    W|  o x00 |", // 3
 "W                                                                    W|        |", // 4
 "W                                                                    W| Inv:   |", // 5
 "W                                                                    W|        |", // 6
 "W                                                                    W|        |", // 7
 "W                                                                    W|  X=00  |", // 8
 "W                  W W     W W     W W      W W                      W|  Y=00  |", // 9 
 "W                  W!W     WHW     WKW      W?W                      W|        |", // 10
 "W                  W5W     W5W     W8W      W5W                      W|--------|", // 11
 "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  P.II: |", // 12
 "W                                                                    W| <3 x3  |", // 13
 "W                                                                    W|  o x00 |", // 14
 "W                                                                    W|        |", // 15
 "W                                                                    W| Inv:   |", // 16
 "W                                                                    W|        |", // 17
 "W                                                                    W|        |", // 18
 "W        *** THIS IS THE SECRET SHOP *** W|        |", // 19
 "W        * ITEM PRICES ARE LISTED UNDER EACH OBJECT                  W|  X=00  |", // 20 
 "W        * TO PURCHASE, SIMPLY STEP ONTO THE ITEM.                   W|  Y=00  |", // 21 
 "W                                                                    W|        |", // 22
 "W                                                                    W|        |", // 23
 "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// ROOM 1 (Dark Room / Switches)
const std::string MAP_ROOM_1[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
     "W/              o           WWWWWWWW          o                      W|  P.I : |", // 1
     "W   WWWWWWWW  WWWWWWWWWWWWW        W              WWWWWW             W| <3 x3  |", // 2
     "W   W      W   o   W   W           W            o W    W             W|  o x00 |", // 3
     "W   W      WWWW    W   W   W   W   WWWWWWWW       W    W             W|        |", // 4
     "W   WWWWWW    W    W   W   W  !W          W       W    WWWWWWW       W| Inv:   |", // 5
     "W        W    W    W   W   WWWWW    WWWWWWW     WWW    W @   W       W|        |", // 6
     "WW1WW    W    W oo W   W        o         W   ooo W    W  K  W       W|        |", // 7
     "W   W    W    WWWWWW   WWWWWWWWWW   WWWWWWW   WWWWW    WWW WWW       W|  X=00  |", // 8
     "W   W    W        oo   W             o              o                W|  Y=00  |", // 9
     "W   W    WWWWWWWWWWW   WWWWWWWWW       WWWWWWW       WWWWWWW      WWWW|        |", // 10
     "W   W               o          W  o          W  !        W        W 2W|--------|", // 11
     "W   WWWWWWWWWWWWWWWWWWWWWW     W  WWWWWWW    W  WWWWWWW WWWWWWW   WWWW|  P.II: |", // 12
     "W        ooo             W     W       W     W      o   W            W| <3 x3  |", // 13
     "W   WWWWWWWWWWWWWWWWWWW  W  WWWWWWWWWWWWWWWWWWWW   WWWWWW            W|  o x00 |", // 14
     "W            !W          W                !    W      o              W|        |", // 15
     "W   WWWWWWWWWWW   WWWWWWWWWWW   WWWWWWWW       W  WWWWWWWWWW         W| Inv:   |", // 16
     "W   Wooo      W   W/ ooooo  W   W      W   o   W  W         W        W|        |", // 17
     "W   Wooo      W   W  ooooo  W   W      W       W  W    o    W        W|        |", // 18
     "W   W   WWWWWWW   W  ooooo  W   WWWWWWWW   WWWWWW  WWWWWWWWWW        W|  X=00  |", // 19
     "W   W             WWWWWWWWWWW    o             o            W        W|  Y=00  |", // 20
     "W   WWWWWW                                       WWWWWWWW   W        W|        |", // 21
     "W        W    WWWWWWWWWWWWWWWWWWWWWWWWW                 W   W        W|        |", // 22
     "W        W    W !                            WWWWW      W   W        W|        |", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// FINAL ROOM
const std::string MAP_ROOM_2[Screen::MAX_Y] = {
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", 0
     "W                                                                              W", 1
     "W                                YOU DID IT!                                   W", 2
     "W                                                                              W", 3
     "W              .g8"" bgd       db      `7MMM.     ,MMF'`7MM" "YMM              W", 4
     "W            .dP'     `M      ;MM:       MMMb    dPMM    MM    `7              W", 5
     "W            dM'       `     ,V^MM.      M YM   ,M MM    MM   d                W", 6
     "W            MM             ,M  `MM      M  Mb  M' MM    MMmmMM                W", 7
     "W            MM.    `7MMF'  AbmmmqMA     M  YM.P'  MM    MM   Y  ,             W", 8
     "W            `Mb.     MM   A'     VML    M  `YM'   MM    MM     ,M             W", 9
     "W              `bmmmdPY .AMA.   .AMMA..JML.   l  .JMML..JMMmmmmMMM             W", 10
     "W                                                                              W", 11
     "W                  .g8""8q.`7MMF'   `7MF'`7MM"" YMM   7MM"" Mq.                W", 12
     "W                .dP'    `YM.`MA     ,V    MM    `7    MM   `MM.               W", 13
     "W                dM'      `MM VM:   ,V     MM   d      MM   ,M9                W", 14
     "W                MM        MM  MM.  M'     MMmmMM      MMmmdM9                 W", 15
     "W                MM.      ,MP  `MM A'      MM   Y  ,   MM  YM.                 W", 16
     "W                `Mb.    ,dP'   :MM;       MM     ,M   MM   `Mb.               W", 17
     "W                   ""bmd""      VF      .JMMmmmmMMM .JMML. .JMM.              W", 18
     "W                                                                              W", 19
     "W                                                                              W", 20
     "W                                                                              W", 21
     "W                                                                              W", 22
     "W                                                                              W", 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  24
};

// GAME OVER ROOM
const std::string MAP_ROOM_3[Screen::MAX_Y] = {
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", 0
     "W                                                                              W", 1
     "W                                  YOU LOST!                                   W", 2
     "W                                                                              W", 3
     "W                                                                              W", 4
     "W                                                                              W", 5
     "W                                                                              W", 6
     "W                                                                              W", 7
     "W                                                                              W", 8
     "W                                                                              W", 9
     "W                                                                              W", 10
     "W                                                                              W", 11
     "W                                                                              W", 12
     "W                                                                              W", 13
     "W                                                                              W", 14
     "W                                                                              W", 15
     "W                                                                              W", 16
     "W                                                                              W", 17
     "W                                                                              W", 18
     "W                                                                              W", 19
     "W                                                                              W", 20
     "W                                                                              W", 21
     "W                                                                              W", 22
     "W                                                                              W", 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  24
};

// --- Game Implementation ---

void game::run_game() {
	hideCursor();
    riddle_manager.loadRiddles("riddles.txt"); // From User 2
	main_menu();
	cls();
}

void game::main_menu() {
    bool exit_requested = false;
    while (!exit_requested) {
        cls();
        gotoxy(0, 0);

        set_text_color(colors ? Color::YELLOW : Color::WHITE);
        std::cout << "=============== WELCOME TO TEXT ADVENTURE WORLD ==============\n";

        set_text_color(colors ? Color::CYAN : Color::WHITE);
        std::cout << "(1) Start a new game\n";
        std::cout << "(4) Toggle Colors (ON/OFF) [Currently: "
            << (colors ? "ON" : "OFF") << "]\n";
        std::cout << "(8) Instructions and keys\n";
        std::cout << "(9) EXIT\n";

        std::cout << "==============================================================\n";

        set_text_color(Color::WHITE);
        std::cout << "Please choose an option: ";

        char choice = _getch();

        switch (choice) {
        case '1': start_new_game(); break;
        case '4': colors = !colors; break;
        case '8': show_instructions(); break;
        case '9': exit_requested = true; break;
        default:
            std::cout << "\nInvalid option. Please try again.\n";
            Sleep(700);
            break;
        }
    }
}

void game::show_instructions() {
    cls();
    gotoxy(0, 0);
    set_text_color(colors ? Color::CYAN : Color::WHITE);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ INSTRUCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Two players move inside the world and must cooperate.\n";
    std::cout << "Movement keys:\n";
    std::cout << "  Player 1: W=UP, D=RIGHT, X=DOWN, A=LEFT, S=STAY, E=THROW\n";
    std::cout << "  Player 2: I=UP, L=RIGHT, M=DOWN, J=LEFT, K=STAY, O=THROW\n";
    std::cout << "\n";
    std::cout << "Press ESC during the game to pause.\n";
    std::cout << "When paused: ESC to resume, 4 to toggle colors, H to go back to main menu.\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INSTRUCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Press any key to go back to the main menu...";
    _getch();
}

void game::start_new_game() {
    current_screen = 0;
    last_riddle_index = riddle_manager.getRandomRiddleIndex(); // User 2 feature
    p1_ready_to_transition = false;
    p2_ready_to_transition = false;
    score = 1000; // Reset score

    Screen screen;
    screen.setGame(this);

    // Try loading file for screen 0, fallback to hardcoded
    bool loadedFromFile = screen.loadFromFile(makeWorldFileName(0));
    if (!loadedFromFile) {
        screen.setMap(MAP_ROOM_0);
    }

    loadObstaclesFromScreen(screen); // User 1's obstacle logic

    screen.draw();

    // Spawn points could be read from file in future, hardcoded for now based on MAP_ROOM_0
    Player players[] = {
        Player(Point(1, 4, 0, 0, '$'),'$', "WADXS", screen),  // P1
        Player(Point(3, 4, 0, 0, '&'),'&', "IJLMK", screen)   // P2
    };

    players[0].setOther(&players[1]);
    players[1].setOther(&players[0]);

    if (current_screen == darkRoomIndex)
        screen.renderWithVisibility(players[0], players[1]);
    else
        screen.renderFull(players[0], players[1]);

    game_loop(screen, players);
}

// User 1's BFS Obstacle Loader
void game::loadObstaclesFromScreen(Screen& screen) {
    obstacles.clear();
    bool visited[Screen::MAX_Y][Screen::MAX_X] = { false };

    for (int y = 0; y < Screen::MAX_Y; ++y) {
        for (int x = 0; x < Screen::MAX_X; ++x) {
            Point p(x, y, '*');
            if (visited[y][x]) continue;
            if (screen.getCharAt(p) != '*') continue;

            std::vector<Point> cells;
            std::stack<Point> st;
            st.push(p);
            visited[y][x] = true;

            while (!st.empty()) {
                Point cur = st.top(); st.pop();
                cells.push_back(cur);

                const int dx[4] = { 1,-1,0,0 };
                const int dy[4] = { 0,0,1,-1 };

                for (int i = 0; i < 4; ++i) {
                    int nx = cur.getX() + dx[i];
                    int ny = cur.getY() + dy[i];

                    if (nx < 0 || ny < 0 || nx >= Screen::MAX_X || ny >= Screen::MAX_Y) continue;
                    if (visited[ny][nx]) continue;

                    Point np(nx, ny, '*');
                    if (screen.getCharAt(np) == '*') {
                        visited[ny][nx] = true;
                        st.push(np);
                    }
                }
            }
            obstacles.emplace_back(cells);
            for (const auto& c : cells)
                screen.setCharAt(c.getX(), c.getY(), ' ');
        }
    }
}

void game::renderFrame(Screen& screen, Player players[]) {
    if (current_screen == darkRoomIndex)
        screen.renderWithVisibility(players[0], players[1]);
    else
        screen.renderFull(players[0], players[1]);
}

bool game::isObstacleAt(int x, int y) const {
    int idx = findObstacleIndexAt(x, y);
    return (idx >= 0 && idx < (int)obstacles.size());
}

void game::game_loop(Screen& screen, Player players[]) {
    bool quitToMenu = false;

    while (!quitToMenu) {
        clearUnlockedDoor(); // Reset door state (User 2)
        
        for (int i = 0; i < 2; ++i) {
            players[i].move();
        }

        updateBomb(screen, players);
        updateScore(screen); // User 2

        if (players[0].isDead() || players[1].isDead()) {
            screen.setMap(MAP_ROOM_3);
            screen.draw();
            gotoxy(0, 24);
            std::cout << "GAME OVER - Press any key to return to main menu...";
            _getch();
            quitToMenu = true;
            continue;
        }

        // --- Transition Logic (Merged) ---
        if (p1_ready_to_transition && p2_ready_to_transition) {
            int nextRoom = current_screen + 1; // Default next
            
            // If User 2's specific destination logic was triggered (e.g., door '9')
            if (p1_dest_room != -1 && p1_dest_room == p2_dest_room) {
                nextRoom = p1_dest_room;
            } else if (p1_dest_room != -1 || p2_dest_room != -1) {
                // If distinct destinations, simple logic: default to +1 or handle specific case
                // For now, let's assume they must agree or we just increment if simple door
                 if (p1_dest_room == 9 || p2_dest_room == 9) nextRoom = 9;
            }

            current_screen = nextRoom;
            p1_ready_to_transition = false;
            p2_ready_to_transition = false;
            p1_dest_room = -1; 
            p2_dest_room = -1;

            bool loaded = screen.loadFromFile(makeWorldFileName(current_screen));

            if (!loaded) {
                // Fallback map loading
                if (current_screen == 1) screen.setMap(MAP_ROOM_1);
                else if (current_screen == 2) screen.setMap(MAP_ROOM_2);
                else if (current_screen == 9) screen.setMap(MAP_ROOM_9);
                else if (current_screen == 0) screen.setMap(MAP_ROOM_0);
                else {
                     // Victory if no more screens?
                    screen.setMap(MAP_ROOM_2); // Win screen
                    // Or just break loop
                }
            }

            loadObstaclesFromScreen(screen);

            // Reset positions based on room (Hardcoded safe spots for fallback)
            if (current_screen == 0) {
                players[0].resetPosition(3, 1);
                players[1].resetPosition(1, 1);
            } else if (current_screen == 9) { // Shop
                players[0].resetPosition(10, 10);
                players[1].resetPosition(12, 10);
            } else { // Standard default start
                players[0].resetPosition(1, 8);
                players[1].resetPosition(3, 8);
            }

            // Sync HUD
            screen.setP1Position(players[0].getX(), players[0].getY());
            screen.setP2Position(players[1].getX(), players[1].getY());
            screen.setP1Coins(players[0].getCoins());
            screen.setP2Coins(players[1].getCoins());
            screen.setP1Hearts(players[0].getHearts());
            screen.setP2Hearts(players[1].getHearts());
            screen.setP1Inventory(players[0].getItem());
            screen.setP2Inventory(players[1].getItem());
            
            renderFrame(screen, players);
        } else {
            renderFrame(screen, players);
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == Keys::ESC) {
                bool goToMenu = handle_pause();
                if (goToMenu) quitToMenu = true;
                else renderFrame(screen, players);
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    players[i].handleKeyPressed(key);
                }
            }
        }
        
        check_switches(screen); // User 2 logic
        Sleep(60); // Balanced sleep
    }
}

bool game::handle_pause() {
	pause_screen();
	bool returnToMenu = false;
	bool stillPaused = true;
	while (stillPaused) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case Keys::ESC: stillPaused = false; break;
			case '4': colors = !colors; pause_screen(); break;
			case 'H': case 'h': returnToMenu = true; stillPaused = false; break;
			default: break;
			}
		}
		Sleep(85);
	}
	return returnToMenu;
}

void game::pause_screen() {
    char choice = 0;
    while (choice != 27 && choice != 'H' && choice != 'h') {
        cls();
        gotoxy(0, 0);
        set_text_color(colors ? Color::CYAN : Color::WHITE);
        std::cout << "================= GAME PAUSED ==================\n";
        set_text_color(colors ? Color::CYAN : Color::WHITE);
        std::cout << "(ESC) Resume Game\n";
        std::cout << "(4) Toggle Colors (ON/OFF) [Currently: " << (colors ? "ON" : "OFF") << "]\n";
        std::cout << "(H) Return to Main Menu\n";
        std::cout << "===============================================\n";
        set_text_color(Color::WHITE);
        std::cout << "Please choose an option: ";

        choice = _getch();
        if (choice == '4') colors = !colors;
    }
}

void game::set_text_color(Color color) {
    if (!colors) return;
    static Color current = Color::WHITE;
    if (color == current) return;
    current = color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

void game::bomb_explode(int bombX, int bombY, Screen& screen, Player players[]) {
    for (int i = 0; i < 2; ++i) {
        int px = players[i].getX();
        int py = players[i].getY();
        if (abs(px - bombX) <= 3 && abs(py - bombY) <= 3) {
            players[i].takeDamage(1);
        }
    }

    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            if (dx == 0 && dy == 0) continue; 
            int x = bombX + dx;
            int y = bombY + dy;
            Point p(x, y, '@'); 

            if (x <= 0 || x >= 79 || y <= 0 || y >= 24) continue; // Boundary check

            if (screen.is_secret_room(p)) {
                screen.setCharAt(x, y, '9');
                continue;
            }

            if (screen.isWall(p)) {
                screen.setCharAt(x, y, ' ');
            }
        }
    }
}

void game::updateBomb(Screen& screen, Player players[]) {
    if (!bombActive) return;

    if (bombTimer <= 1) { 
        bombTimer--;
        if (bombTimer <= 0) {
            bomb_explode(activeBombX, activeBombY, screen, players);
            screen.setCharAt(activeBombX, activeBombY, ' ');
            bombActive = false;
            activeBombX = -1;
            activeBombY = -1;
            bombTimer = 0;
        }
        return;
    }
    bombTimer--;
    if (bombTimer % 2 == 0) screen.setCharAt(activeBombX, activeBombY, '@');
    else screen.setCharAt(activeBombX, activeBombY, ' ');
}

void game::activateBomb(int x, int y) {
    if (bombActive) return;
    bombActive = true;
    activeBombX = x;
    activeBombY = y;
	bombTimer = 10; 
}

// Merged Transition Setter
void game::setPlayerReady(char playerChar, char destChar) {
    int destIndex = -1;
    if (isdigit(destChar)) destIndex = destChar - '0';

    if (playerChar == '$') {
        p1_ready_to_transition = true;
        if(destIndex != -1) p1_dest_room = destIndex;
    }
    else if (playerChar == '&') {
        p2_ready_to_transition = true;
         if(destIndex != -1) p2_dest_room = destIndex;
    }
}

bool game::isPlayerReady(char playerChar) const {
    if (playerChar == '$') return p1_ready_to_transition;
    if (playerChar == '&') return p2_ready_to_transition;
    return false;
}

Color game::get_player_color(char playerChar) const {
    if (!colors) return Color::WHITE;
    if (playerChar == '$') return Color::CYAN;
    if (playerChar == '&') return Color::GREEN;
    return Color::WHITE;
}

int game::findObstacleIndexAt(int x, int y) const {
    for (int i = 0; i < (int)obstacles.size(); ++i) {
        if (obstacles[i].occupies(x, y)) return i;
    }
    return -1;
}

// User 1's Physics Engine
bool game::tryPushObstacle(Screen& screen, Player& p, Player& other, Direction dir, int pBonusPower)
{
    int dx = 0, dy = 0;
    switch (dir) {
    case Direction::LEFT:  dx = -1; break;
    case Direction::RIGHT: dx = 1; break;
    case Direction::UP:    dy = -1; break;
    case Direction::DOWN:  dy = 1; break;
    default: return false;
    }

    int targetX = p.getX() + dx;
    int targetY = p.getY() + dy;

    int idx = findObstacleIndexAt(targetX, targetY);
    if (idx < 0 || idx >= (int)obstacles.size()) return false;

    Obstacle& obs = obstacles[idx];
    int power = 1 + pBonusPower;

    bool otherPushingSameDir = (other.getDiffX() == dx && other.getDiffY() == dy);
    int otherTouchX = other.getX() + dx;
    int otherTouchY = other.getY() + dy;
    bool otherTouchesSameObstacle = (findObstacleIndexAt(otherTouchX, otherTouchY) == idx);
    int behindX = p.getX() - dx;
    int behindY = p.getY() - dy;
    bool otherBehindPusher = (other.getX() == behindX && other.getY() == behindY);

    if (otherPushingSameDir && (otherTouchesSameObstacle || otherBehindPusher)) {
        power += 1;
    }

    if (power < obs.getWeight()) return false;

    for (const auto& c : obs.getCells()) {
        int nx = c.getX() + dx;
        int ny = c.getY() + dy;

        if (nx < 0 || nx >= Screen::MAX_X || ny < 0 || ny >= Screen::MAX_Y) return false;
        if (screen.isHudCell(nx, ny)) return false;

        Point np(nx, ny, ' ');
        if (screen.isWall(np)) return false;
        char bg = screen.getCharAt(np);
        if (bg != ' ') return false;
        if ((nx == p.getX() && ny == p.getY()) || (nx == other.getX() && ny == other.getY())) return false;
        int otherIdx = findObstacleIndexAt(nx, ny);
        if (otherIdx != -1 && otherIdx != idx) return false;
    }

    obs.translate(dir);
    return true;
}

// --- Features from User 2 ---

void game::updateScore(Screen& screen) {
    game_cycle_counter++;
    if (game_cycle_counter >= 5) {
        score--;
        game_cycle_counter = 0;
        screen.setScore(score);
        if (score <= 0) screen.setScore(0);
    }
}

bool game::isDoorUnlocked(int x, int y) const {
    return (unlockedDoorX == x && unlockedDoorY == y);
}

void game::setDoorUnlocked(int x, int y) {
    unlockedDoorX = x;
    unlockedDoorY = y;
}

void game::clearUnlockedDoor() {
    unlockedDoorX = -1;
    unlockedDoorY = -1;
}

bool game::isShopHeart(int x, int y) const {
    if (current_screen != 9) return false;
    if (x == 28 && y == 10) return true;
    return false;
}

bool game::handle_riddle_encounter() {
    int ridx;
    if (last_riddle_index != -1) ridx = last_riddle_index;
    else {
        ridx = riddle_manager.getRandomRiddleIndex();
        if (ridx == -1) return true; 
        last_riddle_index = ridx;
    }

    std::string question = riddle_manager.getQuestion(ridx);
    std::string userInput = "";
    bool inRiddle = true;
    bool solved = false;
    std::string message = "Type answer & Enter, or ESC to leave.";

    while (inRiddle) {
        cls();
        gotoxy(0, 5);
        set_text_color(Color::CYAN);
        std::cout << "=================== RIDDLE ENCOUNTER ===================" << std::endl;
        set_text_color(Color::WHITE);

        gotoxy(1, 8); std::cout << "Riddle: " << question << std::endl;
        gotoxy(1, 12); std::cout << "Your Answer: " << userInput << "_" << std::endl;
        gotoxy(10, 15); set_text_color(Color::YELLOW);
        std::cout << message << std::endl; set_text_color(Color::WHITE);

        char c = _getch();

        if (c == 27) { // ESC
            inRiddle = false; solved = false;
        } else if (c == 13) { // ENTER
            if (riddle_manager.checkAnswer(ridx, userInput)) {
                message = "CORRECT! The path opens.";
                gotoxy(10, 15); set_text_color(Color::GREEN);
                std::cout << message << "                       " << std::endl;
                Sleep(1000);
                inRiddle = false; solved = true;
                last_riddle_index = -1;
            } else {
                message = "WRONG! Try again or ESC.";
                userInput = "";
            }
        } else if (c == 8) { // BACKSPACE
            if (!userInput.empty()) userInput.pop_back();
        } else if (isalnum(c) || c == ' ') {
            userInput += c;
        }
    }
    cls();
    return solved;
}

std::string game::getCurrentClue() const {
    if (last_riddle_index == -1) return "Find a riddle first to get a hint!";
    return riddle_manager.getClue(last_riddle_index);
}

void game::check_switches(Screen& screen) {
    if (current_screen == 1) { // Room 1 specific logic
        char sw1 = screen.getCharAt(Point(1, 1));
        char sw2 = screen.getCharAt(Point(19, 17));

        // Coordinate (66, 11) should probably be blocked unless switched are ON
        // Check if barrier exists at (67, 11) - adjusted from User 2 code
        if (sw1 == '/' && sw2 == '/') {
             if (screen.getCharAt(Point(66, 11)) == 'W') screen.setCharAt(67, 11, ' ');
        } else {
             if (screen.getCharAt(Point(66, 11)) == ' ') screen.setCharAt(67, 11, 'W');
        }
    }
}