#include <iostream>
#include <conio.h>
#include <windows.h>

#include "game.h"
#include "Screen.h"
#include "utils.h"
#include "Player.h"

enum Keys { ESC = 27 };


//maps
// -------------------  ROOM 0 MAP - THIS IS THE SPAWN ROOM ---------------
const std::string MAP_ROOM_0[Screen::MAX_Y] = {
    // -------------------  ROOM 0 MAP ----------------------
   //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W                                  W1W                             WKW|  P.I : |", // 1
    "W                                                                  WWW| <3 x3  |", // 2
    "W                                                   @                W|  o x00 |", // 3
    "W                                   #                                W|        |", // 4
    "W                                 WWWWW                              W| Inv:   |", // 5
    "W                                                                    W|        |", // 6
    "W                                                                    W|        |", // 7
    "W                   WWWWWWWWW                        !               W|  X=00  |", // 8
    "W        K          WWWWWWWWW         WWW WWW                        W|  Y=00  |", // 9
    "W                    WWWWWWW          WWW WWW                        W|        |", // 10
    "W                     WWWWW           WWW WWW                 #######W|--------|", // 11
    "W                      WWW            WWW WWW                        W|  P.II: |", // 12
    "W                      WWW            WWWWWWW                        W| <3 x3  |", // 13
    "W       @               W             WWWWWWW                        W|  o x00 |", // 14
    "W                       W             WWWWWWW                        W|        |", // 15
    "W                                                                    W| Inv:   |", // 16
    "W                                                 #                  W|        |", // 17
    "W                                                 #                  W|        |", // 18
    "W     WWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  X=00  |", // 19
    "W     WWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  Y=00  |", // 20
    "W     WWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|        |", // 21
    "W                     WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW| score: |", // 22
    "WWWWWWWWWMWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  1000  |", // 23
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// -------------------  ROOM 9 MAP - THIS IS THE SECRET ROOM ---------------
const std::string MAP_ROOM_9[Screen::MAX_Y] = {
    // ------------------- SECRET ROOM MAP (Shop) ----------------------
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
 "W        *** THIS IS THE SECRET SHOP ***                             W|        |", // 19
 "W        * ITEM PRICES ARE LISTED UNDER EACH OBJECT                  W|  X=00  |", // 20 
 "W        * TO PURCHASE, SIMPLY STEP ONTO THE ITEM.                   W|  Y=00  |", // 21 
 "W                                                                    W|        |", // 22
 "W                                                                    W|        |", // 23
 "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// -------------------  ROOM 1 MAP - THIS WILL BE THE DARK ROOM ---------------
const std::string MAP_ROOM_1[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
     "W/              o           WWWWWWWW          o                      W|  P.I : |", // 1
     "W   WWWWWWWW  WWWWWWWWWWWWW        W              WWWWWW             W| <3 x3  |", // 2
     "W   W      W   o   W   W           W            o W    W             W|  o x00 |", // 3
     "W   W      WWWW    W   W   W   W   WWWWWWWW       W    W             W|        |", // 4
     "W   WWWWWW    W    W   W   W  !W          W       W    WWWWWWW       W| Inv:   |", // 5
     "W        W    W    W   W   WWWWW    WWWWWWW     WWW    W @   W       W|        |", // 6
     "WW1 W    W    W oo W   W        o         W   ooo W    W  K  W       W|        |", // 7
     "W   W    W    WWWWWW   WWWWWWWWWW   WWWWWWW   WWWWW    WWW WWW       W|  X=00  |", // 8
     "W   W    W        oo   W             o              o                W|  Y=00  |", // 9
     "W   W    WWWWWWWWWWW   WWWWWWWWW       WWWWWWW       WWWWWWW      WWWW|        |", // 10
     "W                   o             o             !                 W 2W|--------|", // 11
     "W   WWWWWWWWWWWWWWWWWWWWWW     W  WWWWWWW    W  WWWWWWW WWWWWWW   WWWW|  P.II: |", // 12
     "W        ooo             W     W       W     W      o   W            W| <3 x3  |", // 13
     "W   WWWWWWWWWWWWWWWWWWW  W  WWWWWWWWWWWWWWWWWWWW   WWWWWW            W|  o x00 |", // 14
     "W            !W          W                !    W      o              W|        |", // 15
     "W   WWWWWWWWWWW   WWWWWWWWWWW   WWWWWWWW       W  WWWWWWWWWW         W| Inv:   |", // 16
     "W   Wooo      W    / ooooo  W   W      W   o   W  W         W        W|        |", // 17
     "W   Wooo      W   W  ooooo  W   W      W       W  W    o    W        W|        |", // 18
     "W   W   WWWWWWW   W  ooooo  W   WWWWWWWW   WWWWWW  WWWWWWWWWW        W|        |", // 19
     "W   W             WWWWWWWWWWW    o             o            W        W|  X=00  |", // 20
     "W   WWWWWW                                       WWWWWWWW   W        W|  Y=00  |", // 21
     "W        W    WWWWWWWWWWWWWWWWWWWWWWWWW                 W   W        W|        |", // 22
     "W        W    W !                            WWWWW      W   W        W|        |", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// ------------------- FINAL ROOM MAP ----------------------
const std::string MAP_ROOM_2[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
     "W                                                                    W|  P.I : |", // 1
     "W                                                                    W| <3 x3  |", // 2
     "W                                                                    W|  o x00 |", // 3
     "W                                                                    W|        |", // 4
     "W                                                                    W| Inv:   |", // 5
     "W                                                                    W|        |", // 6
     "W                                                                    W|        |", // 7
     "W                                                                    W|  X=00  |", // 8
     "W                               YOU DID IT!                          W|  Y=00  |", // 9
     "W                            ====GAME OVER====                       W|        |", // 10
     "W                                                                    W|--------|", // 11
     "W                                                                    W|  P.II: |", // 12
     "W                                                                    W| <3 x3  |", // 13
     "W                                                                    W|  o x00 |", // 14
     "W                                                                    W|        |", // 15
     "W                                                                    W| Inv:   |", // 16
     "W                                                                    W|        |", // 17
     "W                                                                    W|        |", // 18
     "W                                                                    W|        |", // 19
     "W                                                                    W|  X=00  |", // 20
     "W                                                                    W|  Y=00  |", // 21
     "W                                                                    W|        |", // 22
     "W                                                                    W|        |", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

const std::string MAP_ROOM_3[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
     "W                                                                    W|  P.I : |", // 1
     "W                                                                    W| <3 x3  |", // 2
     "W                                                                    W|  o x00 |", // 3
     "W                                                                    W|        |", // 4
     "W                                                                    W| Inv:   |", // 5
     "W                                                                    W|        |", // 6
     "W                                                                    W|        |", // 7
     "W                                                                    W|  X=00  |", // 8
     "W                           YOU LOST                                 W|  Y=00  |", // 9
     "W                       ====GAME OVER====                            W|        |", // 10
     "W                                                                    W|--------|", // 11
     "W                                                                    W|  P.II: |", // 12
     "W                                                                    W| <3 x3  |", // 13
     "W                                                                    W|  o x00 |", // 14
     "W                                                                    W|        |", // 15
     "W                                                                    W| Inv:   |", // 16
     "W                                                                    W|        |", // 17
     "W                                                                    W|        |", // 18
     "W                                                                    W|        |", // 19
     "W                                                                    W|  X=00  |", // 20
     "W                                                                    W|  Y=00  |", // 21
     "W                                                                    W|        |", // 22
     "W                                                                    W|        |", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};




void game::run_game() {
	hideCursor();
    riddle_manager.loadRiddles("riddles.txt"); 
	main_menu();
	cls();
}


void game::main_menu() {
    bool exit_requested = false;

    while (!exit_requested) {
        cls();
        gotoxy(0, 0);


        // Set Title Color: Yellow if colors are ON, white otherwise
        set_text_color(colors ? Color::YELLOW : Color::WHITE);
        std::cout << "=============== WELCOME TO TEXT ADVENTURE WORLD ==============\n";

        // Set Menu Text Color: Blue if colors are ON, white otherwise
        set_text_color(colors ? Color::CYAN : Color::WHITE);
        std::cout << "(1) Start a new game\n";
        std::cout << "(4) Toggle Colors (ON/OFF) [Currently: "
            << (colors ? "ON" : "OFF") << "]\n";
        std::cout << "(8) Instructions and keys\n";
        std::cout << "(9) EXIT\n";

        // Use the Menu Text Color for the bottom line too, for consistency
        std::cout << "==============================================================\n";

        // Reset to White or the default choice color for the prompt, 
        // especially if the input color isn't managed by set_text_color()
        set_text_color(Color::WHITE);
        std::cout << "Please choose an option: ";

        char choice = _getch();

        switch (choice) {
        case '1':
            start_new_game();
            break;
        case '4':
            colors = !colors;
            break;
        case '8':
            show_instructions();
            break;
        case '9':
            exit_requested = true;
            break;
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
    std::cout << "When paused: ESC to resume,4 to turn ON/OFF colors, H to go back to main menu.\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INSTRUCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Press any key to go back to the main menu...";
    _getch();
}

void game::start_new_game() {
    current_screen = 0;
    last_riddle_index = riddle_manager.getRandomRiddleIndex();
    p1_ready_to_transition = false;
    p2_ready_to_transition = false;

    Screen screen;
    screen.setGame(this);

    screen.draw();

    Player players[] = {
        Player(Point(3, 1, 0, 0, '$'),'$', "WADXS", screen),  // P1
        Player(Point(1,  1, 0, 0, '&'),'&', "IJLMK", screen)   // P2
    };

    players[0].setOther(&players[1]);
    players[1].setOther(&players[0]);

    if (current_screen == darkRoomIndex)
        screen.renderWithVisibility(players[0], players[1]);
    else
        screen.renderFull(players[0], players[1]);

    // Now run the main game loop for this game
    game_loop(screen, players);
}

void game::game_loop(Screen& screen, Player players[]) {
    bool quitToMenu = false;

    while (!quitToMenu) {
        clearUnlockedDoor();
        for (int i = 0; i < 2; ++i) {
            players[i].move();
        }

        updateBomb(screen, players);

        updateScore(screen);

        if (players[0].isDead() || players[1].isDead()) {
            screen.setMap(MAP_ROOM_3);

            screen.draw(); //only map, without players

            gotoxy(0, 24);
            std::cout << "GAME OVER - Press any key to return to main menu...";
            _getch();

            quitToMenu = true;
            continue;
        }

        if (p1_ready_to_transition && p2_ready_to_transition) {
            int dest_room = p1_dest_room;

            current_screen = dest_room;

            p1_ready_to_transition = false;
            p2_ready_to_transition = false;
            p1_dest_room = -1;
            p2_dest_room = -1;

            if (current_screen == 1)
                screen.setMap(MAP_ROOM_1);
            else if (current_screen == 2)
                screen.setMap(MAP_ROOM_2);
            else if (current_screen == 9)
                screen.setMap(MAP_ROOM_9);
            else if (current_screen == 0)
                screen.setMap(MAP_ROOM_0);

            if (current_screen == 0) {
                players[0].resetPosition(3, 1);
                players[1].resetPosition(1, 1);
            }
            else if (current_screen == 9) {
                players[0].resetPosition(10, 10);
                players[1].resetPosition(12, 10);
            }
            else if (current_screen == 2) {
                players[0].resetPosition(3, 2);
                players[1].resetPosition(4, 2);
            }

            players[0].resetPosition(1, 8);
            players[1].resetPosition(3, 8);


            screen.setP1Position(players[0].getX(), players[0].getY());
            screen.setP2Position(players[1].getX(), players[1].getY());

            //save coins information 
            screen.setP1Coins(players[0].getCoins());
            screen.setP2Coins(players[1].getCoins());

            //save hearts information
            screen.setP1Hearts(players[0].getHearts());
            screen.setP2Hearts(players[1].getHearts());

            //save inventory information
            screen.setP1Inventory(players[0].getItem());
            screen.setP2Inventory(players[1].getItem());

            if (current_screen == darkRoomIndex)
                screen.renderWithVisibility(players[0], players[1]);
            else
                screen.renderFull(players[0], players[1]);
        }

        else {
            if (current_screen == darkRoomIndex)
                screen.renderWithVisibility(players[0], players[1]);
            else
                screen.renderFull(players[0], players[1]);
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == Keys::ESC) {
                bool goToMenu = handle_pause();

                if (goToMenu) {
                    quitToMenu = true;
                }
                else {
                    if (current_screen == darkRoomIndex)
                        screen.renderWithVisibility(players[0], players[1]);
                    else
                        screen.renderFull(players[0], players[1]);
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    players[i].handleKeyPressed(key);
                }
            }
        }
        check_switches(screen);
        Sleep(30);
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
			case Keys::ESC:
				stillPaused = false; // Resume game
				break;
			case '4':
				colors = !colors; // Toggle colors
				pause_screen();   // Redraw pause screen with new color setting
				break;
			case 'H':
			case 'h':
				returnToMenu = true; // Exit to main menu
				stillPaused = false;
				break;
			default:
				break; // Ignore other keys
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
        Color menuColor = colors ? Color::CYAN : Color::WHITE;
        set_text_color(menuColor);
        std::cout << "(ESC) Resume Game\n";
        std::cout << "(4) Toggle Colors (ON/OFF) [Currently: "
            << (colors ? "ON" : "OFF") << "]\n";
        std::cout << "(H) Return to Main Menu\n";
        set_text_color(colors ? Color::CYAN : Color::WHITE);
        std::cout << "===============================================\n";

        set_text_color(Color::WHITE);
        std::cout << "Please choose an option: ";

        choice = _getch();

        switch (choice) {
        case '4':
            colors = !colors;
            break;
        case 27:
            break;
        case 'H':
        case 'h':
            break;
        default:
            break;
        }
    }
}

void game::set_text_color(Color color) {
    if (!colors) {
        return; 
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}


void game::bomb_explode(int bombX, int bombY, Screen& screen, Player players[]) {
    for (int i = 0; i < 2; ++i) {
        int px = players[i].getX();
        int py = players[i].getY();

        int dx = px - bombX;
        int dy = py - bombY;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;

        if (dx <= 3 && dy <= 3) {
            players[i].takeDamage(1);
        }
    }

    // --- Phase 1: Diminish adjacent walls (1 unit, including diagonal) ---
    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            if (dx == 0 && dy == 0)
                continue; // Skip bomb center

            int x = bombX + dx;
            int y = bombY + dy;
            Point p(x, y, '@'); // Dummy char, only coords matter for isWall

            // Prevent destroying border walls (columns 0, MAX_X-1 and rows 0, MAX_Y-1)
            if (x <= 0 || x >= 69 || y <= 0 || y >= 24) {
                continue; // Skip this cell if it's on the absolute border
            }

            if (screen.is_secret_room(p)) {
                screen.setCharAt(x, y, '9'); // Reveal door
                continue;
            }

            if (screen.isWall(p)) {
                // Diminish the wall (change 'W' to ' ')
                screen.setCharAt(x, y, ' ');
            }
        }
    }
}

void game::updateBomb(Screen& screen, Player players[]) {
    if (!bombActive) {
        return;
    }
    

    if (bombTimer <= 1) { // is this the last cycle?
        bombTimer--;
        if (bombTimer <= 0) {
            bomb_explode(activeBombX, activeBombY, screen, players);

            // Cleanup
            screen.setCharAt(activeBombX, activeBombY, ' ');
            bombActive = false;
            activeBombX = -1;
            activeBombY = -1;
            bombTimer = 0;
        }
        return;
    }

    // this is not last cycle - do the flashing logic
    bombTimer--;

    // 3. Flashing Logic: even->visible, odd->invisible :)
    if (bombTimer % 2 == 0) {
        screen.setCharAt(activeBombX, activeBombY, '@');
    }
    else {
        screen.setCharAt(activeBombX, activeBombY, ' ');
    }
}

void game::activateBomb(int x, int y) {
	// Check if a bomb is already active - if so, ignore new activation - let me know what u think
    if (bombActive) return;

    // Set the new active bomb state
    bombActive = true;
    activeBombX = x;
    activeBombY = y;
	bombTimer = 10; // Start the 5-cycle timer - for now i did 10 for testing
}

void game::setPlayerReady(char playerChar, char destChar) {
    int destIndex = destChar - '0';

    if (playerChar == '$') {
        p1_ready_to_transition = true;
        p1_dest_room = destIndex;
    }
    else if (playerChar == '&') {
        p2_ready_to_transition = true;
        p2_dest_room = destIndex;
    }
}


bool game::isPlayerReady(char playerChar) const {
    if (playerChar == '$') {
        return p1_ready_to_transition;
    }
    else if (playerChar == '&') {
        return p2_ready_to_transition;
    }
    return false;
}

//colors
Color game::get_player_color(char playerChar) const {
    if (!colors) {
        return Color::WHITE; // Use White if colors are off
    }
    if (playerChar == '$') {
        return Color::CYAN;
    }
    else if (playerChar == '&') {
        return Color::GREEN;
    }
    return Color::WHITE;
}

//score
void game::updateScore(Screen& screen) {
    game_cycle_counter++;

    if (game_cycle_counter >= 5) {
        score--;
        game_cycle_counter = 0;

        screen.set_score(score);

        if (score <= 0) {
            screen.set_score(0);
        }
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
    if (current_screen != 9) {
        return false;
    }

    if (x == 28 && y == 10) {
        return true;
    }

    return false;
}


//riddle
bool game::handle_riddle_encounter() {
    int ridx;

    // 1. STICKY LOGIC: Check if we already have an unsolved riddle
    if (last_riddle_index != -1) {
        // We have an active riddle from before (or the shop), force the player to solve IT.
        ridx = last_riddle_index;
    }
    else {
        // No active riddle, pick a new random one
        ridx = riddle_manager.getRandomRiddleIndex();
        if (ridx == -1) return true; // No riddles loaded

        last_riddle_index = ridx; // Save it as the "Active" riddle
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

        gotoxy(1, 8);
        std::cout << "Riddle: " << question << std::endl;

        gotoxy(1, 12);
        std::cout << "Your Answer: " << userInput << "_" << std::endl;

        gotoxy(10, 15);
        set_text_color(Color::YELLOW);
        std::cout << message << std::endl;
        set_text_color(Color::WHITE);

        char c = _getch();

        if (c == 27) { // ESC
            inRiddle = false;
            solved = false;
            // NOTE: We do NOT reset last_riddle_index here. 
            // It stays saved so the clue works!
        }
        else if (c == 13) { // ENTER
            if (riddle_manager.checkAnswer(ridx, userInput)) {
                message = "CORRECT! The path opens.";
                gotoxy(10, 15);
                set_text_color(Color::GREEN);
                std::cout << message << "                       " << std::endl;
                Sleep(1000);

                inRiddle = false;
                solved = true;

                // 2. SUCCESS LOGIC: Reset the memory
                last_riddle_index = -1;
            }
            else {
                message = "WRONG! Try again or ESC.";
                userInput = "";
            }
        }
        else if (c == 8) { // BACKSPACE
            if (!userInput.empty()) {
                userInput.pop_back();
            }
        }
        else if (isalnum(c) || c == ' ') {
            userInput += c;
        }
    }
    cls();
    return solved;
}



std::string game::getCurrentClue() const {
    if (last_riddle_index == -1) {
        return "Find a riddle first to get a hint!";
    }
    return riddle_manager.getClue(last_riddle_index);
}


void game::check_switches(Screen& screen) {
    if (current_screen == 1) { // Room 1
        char sw1 = screen.getCharAt(Point(1, 1));
        char sw2 = screen.getCharAt(Point(19, 17));

        if (sw1 == '/' && sw2 == '/') {
            // BOTH ON: Remove the wall barrier
            if (screen.getCharAt(Point(66, 11)) == 'W') {
                screen.setCharAt(67, 11, ' ');
            }
        }
        else {
            // AT LEAST ONE OFF: Ensure the wall barrier is there
            if (screen.getCharAt(Point(66, 11)) == ' ') {
                screen.setCharAt(67, 11, 'W');
            }
        }
    }
}