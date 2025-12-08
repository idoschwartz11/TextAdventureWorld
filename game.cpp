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
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW1WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  P.I : |", // 1
    "WW            !     WWWWWWWWW             #                          W| <3 x3  |", // 2
    "WW                                        #         @         o      W|  o x00 |", // 3
    "WW                                                                   W|        |", // 4
    "WW                         oooooooooooooooooooooooo                  W| Inv:   |", // 5
    "WW                                                                   W|        |", // 6
    "WW                                                                   W|        |", // 7
    "WW                  WWWWWWWWW                        !               W|  X=00  |", // 8
    "WW       K          WWWWWWWWW         WWW WWW                        W|  Y=00  |", // 9
    "WW                   WWWWWWW          WWW WWW                        W|        |", // 10
    "WW                    WWWWW           WWW WWW                 #######W|--------|", // 11
    "WW                     WWW            WWW WWW                        W|  P.II: |", // 12
    "WW                     WWW            WWWWWWW                        W| <3 x3  |", // 13
    "WW      @               W             WWWWWWW                        W|  o x00 |", // 14
    "WW                      W             WWWWWWW                        W|        |", // 15
    "WW                                                                   W| Inv:   |", // 16
    "WW                                                                   W|        |", // 17
    "WW                                                #                  W|        |", // 18
    "WWWW  WWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|        |", // 19
    "WWWW  WWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  X=00  |", // 20
    "WWWW  WWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|  Y=00  |", // 21
    "WWWW                  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|        |", // 22
    "WWWWWWWWWMWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|        |", // 23
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// -------------------  ROOM 9 MAP - THIS IS THE SECRET ROOM ---------------
const std::string MAP_ROOM_9[Screen::MAX_Y] = {
    // ------------------- SECRET ROOM MAP ----------------------
//01234567890123456789012345678901234567890123456789012345678901234567890123456789
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
"W 1                                                                  W|  P.I : |", // 1
"W                                                                    W| <3 x3  |", // 2
"W                                                                    W|  o x00 |", // 3
"W                                                                    W|        |", // 4
"W                                                                    W| Inv:   |", // 5
"W                                                                    W|        |", // 6
"W                                                                    W|        |", // 7
"W                                                                    W|  X=00  |", // 8
"W                                                                    W|  Y=00  |", // 9
"W                                                                    W|        |", // 10
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


// -------------------  ROOM 1 MAP - THIS WILL BE THE DARK ROOM ---------------
const std::string MAP_ROOM_1[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
     "W 2                                                                  W|  P.I : |", // 1
     "W                                                                    W| <3 x3  |", // 2
     "W                                                                    W|  o x00 |", // 3
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|        |", // 4
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W| Inv:   |", // 5
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|        |", // 6
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|        |", // 7
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|  X=00  |", // 8
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|  Y=00  |", // 9
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|        |", // 10
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|--------|", // 11
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|  P.II: |", // 12
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W| <3 x3  |", // 13
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|  o x00 |", // 14
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                 W|        |", // 15
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

// ------------------- FINAL ROOM MAP ----------------------
const std::string MAP_ROOM_2[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W 1                                                                  W|  P.I : |", // 1
    "W                                                                    W| <3 x3  |", // 2
    "W                                                                    W|  o x00 |", // 3
    "W                                                                    W|        |", // 4
    "W                                                                    W| Inv:   |", // 5
    "W                                                                    W|        |", // 6
    "W                                                                    W|        |", // 7
    "W                                                                    W|  X=00  |", // 8
    "W                          YOU DID IT!                               W|  Y=00  |", // 9
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

const std::string MAP_ROOM_3[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W 1                                                                  W|  P.I : |", // 1
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


const std::string MAP_ROOM_SECRET[Screen::MAX_Y] = {
    // ------------------- SECRET ROOM MAP ----------------------
//01234567890123456789012345678901234567890123456789012345678901234567890123456789
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
"W 1                                                                  W|  P.I : |", // 1
"W                                                                    W| <3 x3  |", // 2
"W                                                                    W|  o x00 |", // 3
"W                                                                    W|        |", // 4
"W                                                                    W| Inv:   |", // 5
"W                                                                    W|        |", // 6
"W                                                                    W|        |", // 7
"W                                                                    W|  X=00  |", // 8
"W                                                                    W|  Y=00  |", // 9
"W                                                                    W|        |", // 10
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
    p1_ready_to_transition = false;
    p2_ready_to_transition = false;

    Screen screen;
    screen.setGame(this);

    screen.draw();

    Player players[] = {
        Player(Point(10, 10, 0, 0, '$'),'$', "WADXS", screen),  // P1
        Player(Point(15,  5, 0, 0, '&'),'&', "IJLMK", screen)   // P2
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
        for (int i = 0; i < 2; ++i) {
            players[i].move();
        }

        updateBomb(screen, players);

        if (players[0].isDead() || players[1].isDead()) {
            screen.setMap(MAP_ROOM_3);

            screen.draw(); //only map, without players

            gotoxy(0, 24);
            std::cout << "GAME OVER - Press any key to return to main menu...";
            _getch();

            quitToMenu = true;
            continue;
        }

		if (p1_ready_to_transition && p2_ready_to_transition) { //room transition only if both ready
            current_screen++;

            p1_ready_to_transition = false;
            p2_ready_to_transition = false;

            if (current_screen == 1)
                screen.setMap(MAP_ROOM_1);
            else if (current_screen == 2)
                screen.setMap(MAP_ROOM_2);
            else if (current_screen == 9)
                screen.setMap(MAP_ROOM_SECRET);

            players[0].resetPosition(10, 10);
            players[1].resetPosition(15, 5);


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

        Sleep(85);
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
            if (x <= 2 || x >= 69 || y <= 2 || y >= 24) {
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

void game::setPlayerReady(char playerChar) {
    if (playerChar == '$') {
        p1_ready_to_transition = true;
    }
    else if (playerChar == '&') {
        p2_ready_to_transition = true;
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