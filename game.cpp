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
"W 1                                                                   |  P.I : |", // 1
"W                                                                     | <3 x3  |", // 2
"W                                                                     |  o x00 |", // 3
"W                                                                     |        |", // 4
"W                                                                     | Inv:   |", // 5
"W                                                                     |        |", // 6
"W                                                                     |        |", // 7
"W                                                                     |  X=00  |", // 8
"W                                                                     |  Y=00  |", // 9
"W                                                                     |        |", // 10
"W                                                                     |--------|", // 11
"W                                                                     |  P.II: |", // 12
"W                                                                     | <3 x3  |", // 13
"W                                                                     |  o x00 |", // 14
"W                                                                     |        |", // 15
"W                                                                     | Inv:   |", // 16
"W                                                                     |        |", // 17
"W                                                                     |        |", // 18
"W                                                                     |        |", // 19
"W                                                                     |  X=00  |", // 20
"W                                                                     |  Y=00  |", // 21
"W                                                                     |        |", // 22
"W                                                                     |        |", // 23
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};


// -------------------  ROOM 1 MAP - THIS WILL BE THE DARK ROOM ---------------
const std::string MAP_ROOM_1[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
     "W 2                                                                   |  P.I : |", // 1
     "W                                                                     | <3 x3  |", // 2
     "W                                                                     |  o x00 |", // 3
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |        |", // 4
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  | Inv:   |", // 5
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |        |", // 6
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |        |", // 7
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |  X=00  |", // 8
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |  Y=00  |", // 9
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |        |", // 10
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |--------|", // 11
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |  P.II: |", // 12
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  | <3 x3  |", // 13
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |  o x00 |", // 14
     "W                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWW                  |        |", // 15
     "W                                                                     | Inv:   |", // 16
     "W                                                                     |        |", // 17
     "W                                                                     |        |", // 18
     "W                                                                     |        |", // 19
     "W                                                                     |  X=00  |", // 20
     "W                                                                     |  Y=00  |", // 21
     "W                                                                     |        |", // 22
     "W                                                                     |        |", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

// ------------------- FINAL ROOM MAP ----------------------
const std::string MAP_ROOM_2[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W 1                                                                   |  P.I : |", // 1
    "W                                                                     | <3 x3  |", // 2
    "W                                                                     |  o x00 |", // 3
    "W                                                                     |        |", // 4
    "W                                                                     | Inv:   |", // 5
    "W                                                                     |        |", // 6
    "W                                                                     |        |", // 7
    "W                                                                     |  X=00  |", // 8
    "W                          YOU DID IT!                                |  Y=00  |", // 9
    "W                       ====GAME OVER====                             |        |", // 10
    "W                                                                     |--------|", // 11
    "W                                                                     |  P.II: |", // 12
    "W                                                                     | <3 x3  |", // 13
    "W                                                                     |  o x00 |", // 14
    "W                                                                     |        |", // 15
    "W                                                                     | Inv:   |", // 16
    "W                                                                     |        |", // 17
    "W                                                                     |        |", // 18
    "W                                                                     |        |", // 19
    "W                                                                     |  X=00  |", // 20
    "W                                                                     |  Y=00  |", // 21
    "W                                                                     |        |", // 22
    "W                                                                     |        |", // 23
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};

const std::string MAP_ROOM_3[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W 1                                                                   |  P.I : |", // 1
    "W                                                                     | <3 x3  |", // 2
    "W                                                                     |  o x00 |", // 3
    "W                                                                     |        |", // 4
    "W                                                                     | Inv:   |", // 5
    "W                                                                     |        |", // 6
    "W                                                                     |        |", // 7
    "W                                                                     |  X=00  |", // 8
    "W                           YOU LOST                                  |  Y=00  |", // 9
    "W                       ====GAME OVER====                             |        |", // 10
    "W                                                                     |--------|", // 11
    "W                                                                     |  P.II: |", // 12
    "W                                                                     | <3 x3  |", // 13
    "W                                                                     |  o x00 |", // 14
    "W                                                                     |        |", // 15
    "W                                                                     | Inv:   |", // 16
    "W                                                                     |        |", // 17
    "W                                                                     |        |", // 18
    "W                                                                     |        |", // 19
    "W                                                                     |  X=00  |", // 20
    "W                                                                     |  Y=00  |", // 21
    "W                                                                     |        |", // 22
    "W                                                                     |        |", // 23
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
};


const std::string MAP_ROOM_SECRET[Screen::MAX_Y] = {
    // ------------------- SECRET ROOM MAP ----------------------
//01234567890123456789012345678901234567890123456789012345678901234567890123456789
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
"W 1                                                                   |  P.I : |", // 1
"W                                                                     | <3 x3  |", // 2
"W                                                                     |  o x00 |", // 3
"W                                                                     |        |", // 4
"W                                                                     | Inv:   |", // 5
"W                                                                     |        |", // 6
"W                                                                     |        |", // 7
"W                                                                     |  X=00  |", // 8
"W                                                                     |  Y=00  |", // 9
"W                                                                     |        |", // 10
"W                                                                     |--------|", // 11
"W                                                                     |  P.II: |", // 12
"W                                                                     | <3 x3  |", // 13
"W                                                                     |  o x00 |", // 14
"W                                                                     |        |", // 15
"W                                                                     | Inv:   |", // 16
"W                                                                     |        |", // 17
"W                                                                     |        |", // 18
"W                                                                     |        |", // 19
"W                                                                     |  X=00  |", // 20
"W                                                                     |  Y=00  |", // 21
"W                                                                     |        |", // 22
"W                                                                     |        |", // 23
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


        // Set Title Color: Yellow if colors are ON, White otherwise
        set_text_color(colors ? Color::YELLOW : Color::WHITE);
        std::cout << "=============== WELCOME TO TEXT ADVENTURE WORLD ==============\n";

        // Set Menu Text Color: Blue if colors are ON, White otherwise
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

        // --- End of Conditional Color Logic ---

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
    // התחלה – חדר 0
    current_screen = 0;
    p1_ready_to_transition = false;
    p2_ready_to_transition = false;

    Screen screen;
    screen.setGame(this);

    // חדר 0 – המפה הבסיסית היא זו שמוגדרת בתוך Screen::screen
    screen.draw();

    Player players[] = {
        Player(Point(10, 10, 0, 0, '$'),'$', "WADXS", screen),  // P1
        Player(Point(15,  5, 0, 0, '&'),'&', "IJLMK", screen)   // P2
    };

    players[0].setOther(&players[1]);
    players[1].setOther(&players[0]);

    // חדר 0 – מואר (לא חשוך), לכן משתמשים ב־renderFull
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
        // 1. תזוזת שחקנים
        for (int i = 0; i < 2; ++i) {
            players[i].move();
        }

        // 2. עדכון פצצה (כולל נזק אם התפוצצה)
        updateBomb(screen, players);

        // 3. בדיקת GAME OVER אחרי פצצה / תזוזה
        if (players[0].isDead() || players[1].isDead()) {
            screen.setMap(MAP_ROOM_3);

            // מציירים רק את המפה, בלי שחקנים
            screen.draw();

            // הודעה למטה
            gotoxy(0, 24);
            std::cout << "GAME OVER - Press any key to return to main menu...";
            _getch();

            quitToMenu = true;
            continue;
        }

        // 4. בדיקה אם שני השחקנים "נכנסו לדלת" ומוכנים למעבר חדר
        if (p1_ready_to_transition && p2_ready_to_transition) {
            // קידום חדר נוכחי (0 -> 1 -> 2 ...)
            current_screen++;

            // איפוס דגלים
            p1_ready_to_transition = false;
            p2_ready_to_transition = false;

            // טעינת המפה המתאימה לפי החדר
            if (current_screen == 1)
                screen.setMap(MAP_ROOM_1);
            else if (current_screen == 2)
                screen.setMap(MAP_ROOM_2);
            else if (current_screen == 9)
                screen.setMap(MAP_ROOM_SECRET);
            // אם תרצי חדרים נוספים – תוסיפי כאן עוד else if

            // איפוס מיקום שחקנים בחדר החדש
            players[0].resetPosition(10, 10);
            players[1].resetPosition(15, 5);

            // --- עדכון HUD אחרי טעינת המפה החדשה ---

            // מיקום שחקנים
            screen.setP1Position(players[0].getX(), players[0].getY());
            screen.setP2Position(players[1].getX(), players[1].getY());

            // מטבעות (נשמרים מתוך השחקנים)
            screen.setP1Coins(players[0].getCoins());
            screen.setP2Coins(players[1].getCoins());

            // לבבות – נשמרים גם במעבר חדרים
            screen.setP1Hearts(players[0].getHearts());
            screen.setP2Hearts(players[1].getHearts());

            // אינבנטר
            screen.setP1Inventory(players[0].getItem());
            screen.setP2Inventory(players[1].getItem());

            // ציור לפי אם החדר חשוך או לא
            if (current_screen == darkRoomIndex)
                screen.renderWithVisibility(players[0], players[1]);
            else
                screen.renderFull(players[0], players[1]);
        }
        else {
            // 5. אין מעבר חדר – פשוט לצייר את הפריים הנוכחי
            if (current_screen == darkRoomIndex)
                screen.renderWithVisibility(players[0], players[1]);
            else
                screen.renderFull(players[0], players[1]);
        }

        // 6. קלט מקשים
        if (_kbhit()) {
            char key = _getch();
            if (key == Keys::ESC) {
                bool goToMenu = handle_pause();

                if (goToMenu) {
                    quitToMenu = true;
                }
                else {
                    // חוזרים מהפאוז – מציירים מחדש לפי סוג החדר
                    if (current_screen == darkRoomIndex)
                        screen.renderWithVisibility(players[0], players[1]);
                    else
                        screen.renderFull(players[0], players[1]);
                }
            }
            else {
                // מעבירים את המקשים לשני השחקנים
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
    // --- שלב 0: נזק לשחקנים ברדיוס 3 ---
    for (int i = 0; i < 2; ++i) {
        int px = players[i].getX();
        int py = players[i].getY();

        int dx = px - bombX;
        int dy = py - bombY;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;

        // ריבוע של 7x7 סביב הפצצה (כמו ה-loop של הקיר)
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