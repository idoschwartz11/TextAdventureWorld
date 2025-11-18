#include <iostream>
#include <conio.h>
#include <windows.h>

#include "game.h"
#include "Screen.h"
#include "utils.h"
#include "Player.h"

//hello


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

        set_text_color(Color::YELLOW);
        std::cout << "=============== WELCOME TO TEXT ADVENTURE WORLD ==============\n";
        set_text_color(Color::WHITE);
        std::cout << "(1) Start a new game\n";
        std::cout << "(4) Toggle Colors (ON/OFF) [Currently: "
            << (colors ? "ON" : "OFF") << "]\n";
        std::cout << "(8) Instructions and keys\n";
        std::cout << "(9) EXIT\n";
        std::cout << "==============================================================\n";
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
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ INSTRUCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Two players move inside the world and must cooperate.\n";
    std::cout << "Movement keys:\n";
    std::cout << "  Player 1: W=UP, D=RIGHT, X=DOWN, A=LEFT, S=STAY, E=THROW\n";
    std::cout << "  Player 2: I=UP, L=RIGHT, M=DOWN, J=LEFT, K=STAY,\n";
    std::cout << "\n";
    std::cout << "Press ESC during the game to pause.\n";
    std::cout << "When paused: ESC to resume,4 to turn ON/OFF colors, H to go back to main menu.\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INSTRUCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Press any key to go back to the main menu...";
    _getch();
}

void game::start_new_game() {
    Screen screen;
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
    cls();
    gotoxy(0, 0);

    set_text_color(Color::YELLOW);
    std::cout << "================= GAME PAUSED ==================\n";
    set_text_color(Color::WHITE);
    std::cout << "(ESC) Resume Game\n";
    std::cout << "(4) Toggle Colors (ON/OFF)\n";
    std::cout << "(H) Return to Main Menu\n";
    std::cout << "===============================================\n";
}

void game::set_text_color(Color color) {
    if (!colors) {
        return; 
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}
