#include <iostream>
#include <conio.h>
#include <windows.h>

#include "game.h"
#include "Screen.h"
#include "utils.h"
#include "Player.h"

enum Keys { ESC = 27 };

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
    Screen screen;
    screen.setGame(this);
    screen.draw();

    Player players[] = {
        Player(Point(10, 10, 1, 0, '$'),'$', "WADXS", screen),  // P1
        Player(Point(15,  5, 0, 1, '&'),'&', "IJLMK", screen)   // P2
    };

    // Draw Players
    for (auto& p : players) {
        p.draw();
    }

    // Now run the main game loop for this game
    game_loop(screen, players);
}

void game::game_loop(Screen& screen, Player players[]) {
   bool quitToMenu = false;

   while (!quitToMenu) {
       // 1. Move all players
       for (int i = 0; i < 2; ++i) { // Replace range-based for loop with traditional for loop
           players[i].move();
       }
       updateBomb(screen);

       if (_kbhit()) {
           char key = _getch();
           if (key == Keys::ESC) {
               quitToMenu = handle_pause();
           }
           else {
               // Send key to players (each will decide if it cares)
               for (int i = 0; i < 2; ++i) { // Replace range-based for loop with traditional for loop
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


void game::bomb_explode(int bombX, int bombY, Screen& screen) {
    // --- Phase 1: Diminish adjacent walls (1 unit, including diagonal) ---
    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            if (dx == 0 && dy == 0)
                continue; // Skip bomb center

            int x = bombX + dx;
            int y = bombY + dy;
            Point p(x, y, '@'); // Dummy char, only coords matter for isWall

            // Prevent destroying border walls (columns 0, MAX_X-1 and rows 0, MAX_Y-1)
			// why x == 69?? it leaves us with one W column before the border wall
            if (x <= 2 || x >= 69 || y <= 2 || y >= 23) {
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
    //        // Objects to diminish: coins ('o') ??, keys ('K')?? 
    //        //maybe will move them around rather then just diminishing it... lets think about it
    // 
    //        //if (cell == 'o' || cell == 'K' || cell == '!'){
    //           // screen.setCharAt(x, y, ' ');

    //also - we need to add Player damage logic here too, 
    // maybe take_damage() function in Player class?
}

void game::updateBomb(Screen& screen) {
    if (!bombActive) {
        return;
    }

    if (bombTimer <= 1) { // is this the last cycle?
        bombTimer--;
        if (bombTimer <= 0) {
            bomb_explode(activeBombX, activeBombY, screen);

            // Cleanup
            screen.setCharAt(activeBombX, activeBombY, ' ');
            bombActive = false;
            activeBombX = -1;
            activeBombY = -1;
            bombTimer = 0;
        }
        return;
    }
    //this is not last cycle - do the flashing logic
    bombTimer--;

    // 3. Flashing Logic: even->visible, odd->invisible :)
    if (bombTimer % 2 == 0) {
        screen.setCharAt(activeBombX, activeBombY, '@');
    }
    else {
        screen.setCharAt(activeBombX, activeBombY, ' ');
    }
}



//void game::updateBomb(Screen& screen) {
//    if (!bombActive) {
//        return;
//    }
//
//    bombTimer--;
//
//    if (bombTimer <= 0) {
//		// explode the bomb
//        bomb_explode(activeBombX, activeBombY, screen);
//
//        // Cleanup
//        screen.setCharAt(activeBombX, activeBombY, ' ');
//        bombActive = false;
//        activeBombX = -1;
//        activeBombY = -1;
//        bombTimer = 0;
//    }
//}

void game::activateBomb(int x, int y) {
	// Check if a bomb is already active - if so, ignore new activation - let me know what u think
    if (bombActive) return;

    // Set the new active bomb state
    bombActive = true;
    activeBombX = x;
    activeBombY = y;
	bombTimer = 10; // Start the 5-cycle timer - for now i did 10 for testing
}