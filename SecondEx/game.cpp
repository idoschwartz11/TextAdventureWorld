#include <iostream>
#include <conio.h>
#include <windows.h>
#include "game.h"
#include "Screen.h"
#include "utils.h"
#include "Player.h"
#include <stack>
#include <vector>
#include "Obstacle.h"

enum Keys { ESC = 27 };


//maps
// -------------------  ROOM 0 MAP - THIS IS THE SPAWN ROOM ---------------
const std::string MAP_ROOM_0[Screen::MAX_Y] = {
    // -------------------  ROOM 0 MAP ----------------------
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
    "W  *                                      W   o        W         o   W|        |", // 10
    "W        **    WWWWWWWWWWWWWW      @      W      @     WWWWWWWWWWWWWWW|--------|", // 11
    "W#### **       W            W             W o        o W   W       W1W|  P.II: |", // 12
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

// -------------------  ROOM 9 MAP - THIS IS THE SECRET ROOM ---------------
const std::string MAP_ROOM_9[Screen::MAX_Y] = {
    // ------------------- SECRET ROOM MAP ----------------------
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
 "W                                                                    W|  X=00  |", // 19
 "W                                                                    W|  Y=00  |", // 20
 "W                                                                    W|        |", // 21
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

// ------------------- FINAL ROOM MAP ----------------------
const std::string MAP_ROOM_2[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "W                                                                              W", // 1
     "W                                YOU DID IT!                                   W", // 2
     "W                                                                              W", // 3
     "W              .g8"" bgd       db      `7MMM.     ,MMF'`7MM" "YMM              W", // 4
     "W            .dP'     `M      ;MM:       MMMb    dPMM    MM    `7              W", // 5
     "W            dM'       `     ,V^MM.      M YM   ,M MM    MM   d                W", // 6
     "W            MM             ,M  `MM      M  Mb  M' MM    MMmmMM                W", // 7
     "W            MM.    `7MMF'  AbmmmqMA     M  YM.P'  MM    MM   Y  ,             W", // 8
     "W            `Mb.     MM   A'     VML    M  `YM'   MM    MM     ,M             W", // 9
     "W              `bmmmdPY .AMA.   .AMMA..JML.   l  .JMML..JMMmmmmMMM             W", // 10
     "W                                                                              W", // 11
     "W                  .g8""8q.`7MMF'   `7MF'`7MM"" YMM   7MM"" Mq.                W", // 12
     "W                .dP'    `YM.`MA     ,V    MM    `7    MM   `MM.               W", // 13
     "W                dM'      `MM VM:   ,V     MM   d      MM   ,M9                W", // 14
     "W                MM        MM  MM.  M'     MMmmMM      MMmmdM9                 W", // 15
     "W                MM.      ,MP  `MM A'      MM   Y  ,   MM  YM.                 W", // 16
     "W                `Mb.    ,dP'   :MM;       MM     ,M   MM   `Mb.               W", // 17
     "W                   ""bmd""      VF      .JMMmmmmMMM .JMML. .JMM.              W", // 18
     "W                                                                              W", // 19
     "W                                                                              W", // 20
     "W                                                                              W", // 21
     "W                                                                              W", // 22
     "W                                                                              W", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};

const std::string MAP_ROOM_3[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "W                                                                              W", // 1
     "W                                  YOU LOST!                                   W", // 2
     "W                                                                              W", // 3
     "W              .g8"" bgd       db      `7MMM.     ,MMF'`7MM" "YMM              W", // 4
     "W            .dP'     `M      ;MM:       MMMb    dPMM    MM    `7              W", // 5
     "W            dM'       `     ,V^MM.      M YM   ,M MM    MM   d                W", // 6
     "W            MM             ,M  `MM      M  Mb  M' MM    MMmmMM                W", // 7
     "W            MM.    `7MMF'  AbmmmqMA     M  YM.P'  MM    MM   Y  ,             W", // 8
     "W            `Mb.     MM   A'     VML    M  `YM'   MM    MM     ,M             W", // 9
     "W              `bmmmdPY .AMA.   .AMMA..JML.   l  .JMML..JMMmmmmMMM             W", // 10
     "W                                                                              W", // 11
     "W                  .g8""8q.`7MMF'   `7MF'`7MM"" YMM   7MM"" Mq.                W", // 12
     "W                .dP'    `YM.`MA     ,V    MM    `7    MM   `MM.               W", // 13
     "W                dM'      `MM VM:   ,V     MM   d      MM   ,M9                W", // 14
     "W                MM        MM  MM.  M'     MMmmMM      MMmmdM9                 W", // 15
     "W                MM.      ,MP  `MM A'      MM   Y  ,   MM  YM.                 W", // 16
     "W                `Mb.    ,dP'   :MM;       MM     ,M   MM   `Mb.               W", // 17
     "W                   ""bmd""      VF      .JMMmmmmMMM .JMML. .JMM.              W", // 18
     "W                                                                              W", // 19
     "W                                                                              W", // 20
     "W                                                                              W", // 21
     "W                                                                              W", // 22
     "W                                                                              W", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};


const std::string MAP_ROOM_SECRET[Screen::MAX_Y] = {
    // ------------------- SECRET ROOM MAP ----------------------
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
 "W                                                                    W|  X=00  |", // 19
 "W                                                                    W|  Y=00  |", // 20
 "W                                                                    W|        |", // 21
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

    screen.setMap(MAP_ROOM_0);
    loadObstaclesFromScreen(screen);

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

void game::loadObstaclesFromScreen(Screen& screen) {
    obstacles.clear();

    bool visited[Screen::MAX_Y][Screen::MAX_X] = { false };

    for (int y = 0; y < Screen::MAX_Y; ++y) {
        for (int x = 0; x < Screen::MAX_X; ++x) {

            Point p(x, y, '*');
            if (visited[y][x]) continue;
            if (screen.getCharAt(p) != '*') continue;

            // BFS / DFS
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

                    if (nx < 0 || ny < 0 || nx >= Screen::MAX_X || ny >= Screen::MAX_Y)
                        continue;

                    if (visited[ny][nx]) continue;

                    Point np(nx, ny, '*');
                    if (screen.getCharAt(np) == '*') {
                        visited[ny][nx] = true;
                        st.push(np);
                    }
                }
            }

            // Store the obstacle
            obstacles.emplace_back(cells);

            // Clear the obstacle from the screen
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
        for (int i = 0; i < 2; ++i) {
            players[i].move();
        }

        updateBomb(screen, players);

        if (players[0].isDead() || players[1].isDead()) {
            screen.setMap(MAP_ROOM_3);
            screen.draw();

            gotoxy(0, 24);
            std::cout << "GAME OVER - Press any key to return to main menu...";
            _getch();

            quitToMenu = true;
            continue;
        }

        if (p1_ready_to_transition && p2_ready_to_transition) {
            current_screen++;

            p1_ready_to_transition = false;
            p2_ready_to_transition = false;

            if (current_screen == 1) {
                screen.setMap(MAP_ROOM_1);
                loadObstaclesFromScreen(screen);
            }
            else if (current_screen == 2) {
                screen.setMap(MAP_ROOM_2);
                loadObstaclesFromScreen(screen);
            }
            else if (current_screen == 9) {
                screen.setMap(MAP_ROOM_SECRET);
                loadObstaclesFromScreen(screen);
            }

            players[0].resetPosition(1, 8);
            players[1].resetPosition(3, 8);

            screen.setP1Position(players[0].getX(), players[0].getY());
            screen.setP2Position(players[1].getX(), players[1].getY());

            screen.setP1Coins(players[0].getCoins());
            screen.setP2Coins(players[1].getCoins());

            screen.setP1Hearts(players[0].getHearts());
            screen.setP2Hearts(players[1].getHearts());

            screen.setP1Inventory(players[0].getItem());
            screen.setP2Inventory(players[1].getItem());

            renderFrame(screen, players);
        }
        else {
            renderFrame(screen, players);
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == Keys::ESC) {
                bool goToMenu = handle_pause();

                if (goToMenu) {
                    quitToMenu = true;
                }
                else {
                    renderFrame(screen, players);
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

int game::findObstacleIndexAt(int x, int y) const {
    for (int i = 0; i < (int)obstacles.size(); ++i) {
        if (obstacles[i].occupies(x, y))
            return i;
    }
    return -1;
}

bool game::tryPushObstacle(Screen& screen, Player& p, Player& other, Direction dir, int pBonusPower)
{
    int dx = 0, dy = 0;
    switch (dir) {
    case Direction::LEFT:  dx = -1; break;
    case Direction::RIGHT: dx = 1; break;
    case Direction::UP:    dy = -1; break;
    case Direction::DOWN:  dy = 1; break;
    default:
        return false;
    }

    int targetX = p.getX() + dx;
    int targetY = p.getY() + dy;

    int idx = findObstacleIndexAt(targetX, targetY);
    if (idx < 0 || idx >= (int)obstacles.size())
        return false;

    Obstacle& obs = obstacles[idx];

    int power = 1 + pBonusPower;

    // other must be actively pushing same direction NOW
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

    if (power < obs.getWeight())
        return false;

    for (const auto& c : obs.getCells()) {
        int nx = c.getX() + dx;
        int ny = c.getY() + dy;

        // screen bounds
        if (nx < 0 || nx >= Screen::MAX_X || ny < 0 || ny >= Screen::MAX_Y)
            return false;

        // HUD zone
        if (screen.isHudCell(nx, ny))
            return false;

        Point np(nx, ny, ' ');

        // walls
        if (screen.isWall(np))
            return false;

        char bg = screen.getCharAt(np);
        if (bg != ' ')
            return false;

        if ((nx == p.getX() && ny == p.getY()) || (nx == other.getX() && ny == other.getY()))
            return false;

        int otherIdx = findObstacleIndexAt(nx, ny);
        if (otherIdx != -1 && otherIdx != idx)
            return false;
    }

    obs.translate(dir);
    return true;
}

