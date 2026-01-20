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
#include <fstream>
#include "KeyboardRecorder.h"
#include "FileInputPlayer.h"





static std::string makeWorldFileName(int idx)
{
    std::ostringstream os;
    os << "adv-world_" << std::setw(2) << std::setfill('0') << idx << ".screen";
    return os.str();
}

const std::string MAP_ROOM_0[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "L                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "                    WWWWWW          o o o o o o o              W              WW ", // 1
     "                    W  #  W                                    W              WW ", // 2
     "WWWWWWWWWWWWWWWWWWWWW  #  W     WWWWWWWWWWWWWWWWWWW         WWW   WWWWWWWWW    W", // 3
     "W         W   W        #  W     W       W         W         W     W  oo   W    W", // 4
     "W   WWWWWWW   W        #  W     W       W         W    @    W     W  oo   W    W", // 5
     "W   W     W          W  W       W       W         WWWWWWWWWWW     WWWWWWWWW    W", // 6
     "W   W     W          W** W      W       W                                      W", // 7
     "W   W     W          W   W      W       W           WWWWWWWWWWWWW              W", // 8
     "W   W     W          W @ W      WWWWWWWWWWWWWWWW    W            W             W", // 9
     "W                    WWWWW                          W            W             W", // 10
     "W              WWWWWWWWWWWWWW                       W            WWWWWWWWWWWWWWW", // 11
     "W              W            W                       W            W           W1W", // 12
     "W   WWWWWWWW   W   oooooo   W     WWWWWW  WWWWWWWWWWW          WWW           WWW", // 13
     "W   W  oo  W   W            W     W    W  W                          W         W", // 14
     "W   W  oo  W   W            W     W    W  W                           WWWWWWWWWW", // 15
     "W   W      W   WWWWW**WWWWWWW     WWWWWW  WWWWWWWWWWWWWWWWWWWWWWWWWWW    W     W", // 16
     "W   WWWWWWWW                                                        W    W     W", // 17
     "W                                 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W     W", // 18
     "W                                 W       ooo  @  ooo    W                     W", // 19
     "W                                 W          ooooo       W                     W", // 20
     "W                                 R                      W                     W", // 21
     "W                                 W                      W                     W", // 22
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWMWWWWWWWWW", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};

// ROOM 9 (Shop/Secret) - User 2's design
const std::string MAP_ROOM_9[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "L                    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "                     W                                                         W", // 1
     "                     W                                                         W", // 2
     "WWWWWWWW0WWWWWWWWWWWWW                                                         W", // 3
     "W                                                                              W", // 4
     "W                                                                              W", // 5
     "W                                                                              W", // 6
     "W                                                                              W", // 7
     "W                                                                              W", // 8
     "W                         W W     W W     W W      W W                         W", // 9 
     "W                         W!W     WHW     WKW      W?W                         W", // 10
     "W                         W5W     W5W     W8W      W5W                         W", // 11
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**WWWWWWWWWW", // 12
     "W                                                               W   ##         W", // 13
     "W                                                               W   ##         W", // 14
     "W                                                               W   WW         W", // 15
     "W                                                               W              W", // 16
     "W                                                               W              2", // 17
     "W                                                               W              W", // 18
     "W                   *** THIS IS THE SECRET SHOP ***             W              W", // 19
     "W                 * ITEM PRICES ARE UNDER EACH OBJECT           W              W", // 20 
     "W                  * TO PURCHASE,STEP ONTO THE ITEM.            W              W", // 21 
     "W                                                               W   K          W", // 22
     "W                                                               W              W", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};

// ROOM 1 (Dark Room / Switches)
const std::string MAP_ROOM_1[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "L                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "                    W                  WWWWWWWW                                W", // 1
     "                    WWWWWWWW  WWWWWWWWWWWWW        W          WWWWWW           W", // 2
     "WWWWWWWWWWWWWWWWWWWW                      W     ooooooo       W                W", // 3
     "W2        R ! W  /                        W @   oo / oo       W                W", // 4
     "W         WWWWWWWWWWWWW                   WWWWWWWWWWWWWWWWWWWWW                W", // 5
     "W                                                                              W", // 6
     "W   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W", // 7
     "W   W                                                                     W    W", // 8
     "W   W    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W    W", // 9
     "W   W    W         W                                       W         W    W    W", // 10
     "0   W    W  oooo   W       IM SCARED...                    W    @    W    W    W", // 11
     "W   W    W  oooo   W                                       W         W    W    W", // 12
     "W   W    W         W                                       W         W    W    W", // 13
     "W   W    WWWWWWWWWWW                                       WWWWWWWWWWW    W    W", // 14
     "W   W                                                                     W    W", // 15
     "W   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W", // 16
     "W                               W                   W                          W", // 17
     "WWWWWWWWWWWWWWWWWWWWWW          W                   W           WWWWWWWWWWWWWWWW", // 18
     "W @            W                W         !         W           W            @ W", // 19
     "W      /       W                W         W         W           W      /       W", // 20
     "W    ooooo     W                W         W         W           W    ooooo     W", // 21
     "W    ooooo     W    WWWWWWWWWWWWW    WWWWWWWWWWW    WWWWWWWWWWWWW    ooooo     W", // 22
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 23
     "                                                                                "  // 24
};


const std::string MAP_ROOM_2[Screen::MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "L                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "                    WWWWW                                                      W", // 1
     "                    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 2
     "WWWWWWWWWWWWWWWWWWWW            *            W            *                    W", // 3
     "W1    W            W            W            *            W                    W", // 4
     "W     WWWWWW  WWWWWWWWWWWWW*WW  WWWWWWWWWWWWWWWW  WWWWWWWWWWWWWWWW  WWWWWWWWWWWW", // 5
     "W          W  W              W  W              W  W                 W          W", // 6
     "W          W  W              W  W              W  W              W  W          W", // 7
     "WWWWWWWWW**W  W  WWWWWWWWWW*WW  W WWWWWWWWWWW*WW  WW WWWWWWWWWWWWW**W  WWWWWWWWW", // 8
     "W     *    W  W  W        W WW  W WW        W WW  WW W        W                W", // 9
     "W     *    W  W  W        W WW  W WW  o o o W WW  WW W        W  W  W        K W", // 10
     "WW**WWWWWWWWWWW**W        W WWWWW*WW  o o o W WWWWWW*W        W  WWWWWWWWWWWW*WW", // 11
     "W                W        W        W  o o o W        W        W        W       W", // 12
     "W                W        W   @    W        W        W                 W       W", // 13
     "WWWWWWWWWWWWWWWWWW        WWWWWWWWWW        WWWWWWWWWW        WWWWWWWWWW       W", // 14
     "W              W                                  *                            W", // 15
     "W              W                                  *                            W", // 16
     "WWWWWWWWWWWWWWWWWW**WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 17
     "W                W  W                                  W  W  *                 W", // 18
     "W                W  *   W                              W     W                 W", // 19
     "W  WWWWWWWWWWWW  W  W  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**W**W**WWWWWWWWWWRWWWWWWWW", // 20
     "W  W          W  W  W  W                            W  WooW  W                 W", // 21
     "W  W          W  W  W  W                            W     W  W                 W", // 22
     "W  WWWWWWWWWWWW  W  W  WWWWWWWWWWMWWWWWWWWWWWWWWWWWWW     W  W                3W", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};


// FINAL ROOM
const std::string MAP_ROOM_3[Screen::MAX_Y] = {
     "L                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "                    W                                                    #     W", // 1
     "                    W                                                    #     W", // 3
     "WWWWWWWWWWWWWWWWWWWWW                                                    #     W", // 2
     "W                                                                        #     W", // 4
     "W                                                                        #     W", // 5
     "W                                                                        #     W", // 6
     "W                                  YOU DID IT                                  W", // 7
     "W              .g8"" bgd       db      `7MMM.     ,MMF'`7MM" "YMM        o     W", // 8
     "W            .dP'     `M      ;MM:       MMMb    dPMM    MM    `7        o     W", // 9
     "W            dM'       `     ,V^MM.      M YM   ,M MM    MM   d          o     W", // 10
     "W            MM             ,M  `MM      M  Mb  M' MM    MMmmMM          o     W", // 11
     "W            MM.    `7MMF'  AbmmmqMA     M  YM.P'  MM    MM   Y  ,       o     W", // 12
     "W            `Mb.     MM   A'     VMU    M  `YM'   MM    MM     ,M       o     W", // 13
     "W              `bmmmdPY .AMA.   .AMMA..JMU.   l  .JMMU..JMMmmmmMMM       o     W", // 14
     "W######                                                                        W", // 15
     "W                  .g8""8q.`7MMF'   `7MF'`7MM"" YMM   7MM"" Mq.                W", // 16
     "W                .dP'    `YM.`MA     ,V    MM    `7    MM   `MM.               W", // 17
     "W                dM'      `MM VM:   ,V     MM   d      MM   ,M9                W", // 18
     "W                MM        MM  MM.  M'     MMmmMM      MMmmdM9                 W", // 19
     "W                MM.      ,MP  `MM A'      MM   Y  ,   MM  YM.                 W", // 20
     "W                `Mb.    ,dP'   :MM;       MM     ,M   MM   `Mb.               W", // 21
     "W                   ""bmd""      VF      .JMMmmmmMMM .JMMU. .JMM.              W", // 22
     "W                                                                              W", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};

// GAME OVER ROOM
const std::string MAP_ROOM_3_lost[Screen::MAX_Y] = {
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
     "W                                                                              W", // 1
     "W                                                                              W", // 2
     "W                                                                              W", // 3
     "W                                  YOU DIED                                    W", // 4
     "W                                                                              W", // 5
     "W                                                                              W", // 6
     "W                                                                              W", // 7
     "W              .g8"" bgd       db      `7MMM.     ,MMF'`7MM" "YMM              W", // 8
     "W            .dP'     `M      ;MM:       MMMb    dPMM    MM    `7              W", // 9
     "W            dM'       `     ,V^MM.      M YM   ,M MM    MM   d                W", // 10
     "W            MM             ,M  `MM      M  Mb  M' MM    MMmmMM                W", // 11
     "W            MM.    `7MMF'  AbmmmqMA     M  YM.P'  MM    MM   Y  ,             W", // 12
     "W            `Mb.     MM   A'     VMU    M  `YM'   MM    MM     ,M             W", // 13
     "W              `bmmmdPY .AMA.   .AMMA..JMU.   l  .JMMU..JMMmmmmMMM             W", // 14
     "W                                                                              W", // 15
     "W                  .g8""8q.`7MMF'   `7MF'`7MM"" YMM   7MM"" Mq.                W", // 16
     "W                .dP'    `YM.`MA     ,V    MM    `7    MM   `MM.               W", // 17
     "W                dM'      `MM VM:   ,V     MM   d      MM   ,M9                W", // 18
     "W                MM        MM  MM.  M'     MMmmMM      MMmmdM9                 W", // 19
     "W                MM.      ,MP  `MM A'      MM   Y  ,   MM  YM.                 W", // 20
     "W                `Mb.    ,dP'   :MM;       MM     ,M   MM   `Mb.               W", // 21
     "W                   ""bmd""      VF      .JMMmmmmMMM .JMMU. .JMM.              W", // 22
     "W                                                                              W", // 23
     "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
};




// --- Game Implementation ---

void game::run_game(int argc, char* argv[]) {
    total_global_time = 0;
    bool isLoadMode = false;
    bool isSaveMode = false;

    if (argc > 1) {
        std::string mode = argv[1];
        if (mode == "-save") isSaveMode = true;
        else if (mode == "-load") isLoadMode = true;

        if (argc > 2 && std::string(argv[2]) == "-silent")
            isSilent = true;
    }

    unsigned int seed = static_cast<unsigned int>(time(nullptr));

    if (isLoadMode) {
        inputSource = new FileInputPlayer("adv-world.steps");
        unsigned int fileSeed = static_cast<FileInputPlayer*>(inputSource)->getSeed();
        if (fileSeed != 0) seed = fileSeed;
    }
    else {
        inputSource = new KeyboardRecorder(seed, isSaveMode);
    }

    std::srand(seed);

    hideCursor();
    riddle_manager.loadRiddles("riddles.txt");

    if (isLoadMode) {
        start_new_game();
    }
    else {
        main_menu();
    }

    delete inputSource;
    inputSource = nullptr;
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
    current_game_cycle = 0;
    last_riddle_index = riddle_manager.getRandomRiddleIndex();
    p1_ready_to_transition = false;
    p2_ready_to_transition = false;
    score = 1000;

    Screen screen;
    screen.setGame(this);

    bool loadedFromFile = screen.loadFromFile(makeWorldFileName(0));
    if (!loadedFromFile) {
        screen.setMap(MAP_ROOM_0);
    }

    loadLevelConfig(0);

    loadObstaclesFromScreen(screen);

    screen.draw();

    Player players[] = {
        Player(Point(1, 4, 0, 0, '$'),'$', "WADXS", screen),
        Player(Point(3, 4, 0, 0, '&'),'&', "IJLMK", screen)
    };

    players[0].setOther(&players[1]);
    players[1].setOther(&players[0]);

    if (isCurrentLevelDark)
        screen.renderWithVisibility(players[0], players[1]);
    else
        screen.renderFull(players[0], players[1]);

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
    if (isCurrentLevelDark)
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
    int deathScreenTimer = 0;

    while (!quitToMenu) {
        clearUnlockedDoor();

        // ===== 1) INPUT =====
        char key = 0;
        bool hasInput = false;

        if (inputSource) {
            hasInput = inputSource->hasInput(total_global_time, key);
        }

        if (hasInput) {
            if (key == KEY_ESC) { 
                if (!isSilent) {
                    bool goToMenu = handle_pause();
                    if (goToMenu) quitToMenu = true;
                    else if (!isSilent) renderFrame(screen, players);
                }
            }
            else {
                if (current_screen != 99) {
                    for (int i = 0; i < 2; ++i) players[i].handleKeyPressed(key);
                }
            }
        }

        // ===== 2) UPDATE =====
        if (current_screen != 99) {
            for (int i = 0; i < 2; ++i) players[i].move();
            updateBomb(screen, players);
            updateScore(screen);
        }

        // ===== 3) GAME OVER LOGIC =====
        if ((players[0].isDead() || players[1].isDead()) && current_screen != 99) {

            logEvent("GAME_OVER_DEATH SCORE " + std::to_string(score));
            std::ofstream resFile("adv-world.result");
            if (resFile.is_open()) {
                for (const auto& line : resultsLog) resFile << line << std::endl;
            }

            p1_dest_room = 99;
            p2_dest_room = 99;
            p1_ready_to_transition = true;
            p2_ready_to_transition = true;

            deathScreenTimer = 0;
        }

        if (current_screen == 99) {
            deathScreenTimer++;
            if (deathScreenTimer > 30 && hasInput) {
                quitToMenu = true;
            }
        }

        // ===== 4) SCREEN TRANSITION =====
        if (p1_ready_to_transition && p2_ready_to_transition) {
            int next_r = (p1_dest_room != -1) ? p1_dest_room : (current_screen + 1);

            logEvent("SCREEN_TRANSITION " + std::to_string(next_r));

            visitedRooms[current_screen] = screen.getMapState(obstacles);
            visitedRoomLocks[current_screen] = screen.getLocksState();

            int prev_room = current_screen;
            current_screen = next_r;

            loadLevelConfig(current_screen);

            p1_ready_to_transition = false;
            p2_ready_to_transition = false;
            p1_dest_room = -1;
            p2_dest_room = -1;

            if (visitedRooms.count(current_screen)) {
                screen.setMapFromState(visitedRooms[current_screen]);
            }
            else {
                std::string filename = makeWorldFileName(current_screen);
                bool loaded = screen.loadFromFile(filename);
                if (!loaded) {
                    if (current_screen == 99) screen.setMap(MAP_ROOM_3_lost); 
                    else if (current_screen == 3) screen.setMap(MAP_ROOM_3);
                    else {
                        if (!isSilent) {
                            cls();
                            std::cout << "Error loading file: " << filename << "\nPress any key to exit.";
                            _getch();
                        }
                        quitToMenu = true;
                    }
                }
            }

            if (visitedRoomLocks.count(current_screen)) screen.setLocksState(visitedRoomLocks[current_screen]);
            else screen.resetUnlockedDoors();

            loadObstaclesFromScreen(screen);

            int p1x = 2, p1y = 5;
            int p2x = 4, p2y = 5;

            if (current_screen == 0) {
                if (prev_room == 1) { p1x = 75; p1y = 12; p2x = 75; p2y = 13; }
                else { p1x = 3; p1y = 4; p2x = 1; p2y = 4; }
            }

            players[0].resetPosition(p1x, p1y);
            players[1].resetPosition(p2x, p2y);
            screen.setP1Position(p1x, p1y);
            screen.setP2Position(p2x, p2y);

            if (!isSilent && !quitToMenu) {
                if (current_screen == darkRoomIndex) screen.renderWithVisibility(players[0], players[1]);
                else screen.renderFull(players[0], players[1]);
            }
        }
        else {
            if (!isSilent && current_screen != 99) {
                renderFrame(screen, players);
            }
        }

        // ===== 5) OTHER UPDATES =====
        check_switches(screen);

        // ===== 6) TIME & SLEEP =====
        total_global_time++;
        Sleep(isSilent ? 0 : 60);
    }
}


void game::pause_screen() {
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
}

bool game::handle_pause() {
    pause_screen();

    bool returnToMenu = false;
    bool stillPaused = true;

    while (stillPaused) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case KEY_ESC:
                stillPaused = false;
                break;
            case '4':
                colors = !colors;
                pause_screen(); 
                break;
            case 'H':
            case 'h':
                returnToMenu = true;
                stillPaused = false;
                break;
            default: break;
            }
        }
        //Sleep(85);
    }
    return returnToMenu;
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
            logEvent("lost_life Player " + std::to_string(i + 1) + " Hearts_Left:" + std::to_string(players[i].getHearts()));
            if (players[i].isDead()) {
                logEvent("PLAYER_DIED Player " + std::to_string(i + 1));
            }
        }
    }

    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int x = bombX + dx;
            int y = bombY + dy;
            Point p(x, y, '@');

            if (x <= 0 || x >= 79 || y <= 0 || y >= 24) continue; // Boundary check
            if (x <= 21 && y <= 4)
                continue;
            if (screen.isHudCell(x, y)) continue;

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

void game::setPlayerReady(char playerChar, char destChar) {
    int destIndex = -1;
    if (isdigit(destChar)) destIndex = destChar - '0';

    if (playerChar == '$') {
        p1_ready_to_transition = true;
        if (destIndex != -1) p1_dest_room = destIndex;
    }
    else if (playerChar == '&') {
        p2_ready_to_transition = true;
        if (destIndex != -1) p2_dest_room = destIndex;
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

bool game::tryPushObstacle(Screen& screen, Player& p, Player& other, Direction dir, int pBonusPower)
{
    // Implementation same as before, essentially
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
    std::string message = "Type answer. Press ENTER (or '1') to submit.";

    if (!isSilent) cls();

    if (inputSource) inputSource->setRiddleMode(true);

    while (inRiddle) {
        total_global_time++;

        if (!isSilent) {
            gotoxy(0, 5); set_text_color(Color::CYAN);
            std::cout << "=================== RIDDLE ENCOUNTER ===================" << std::endl;
            set_text_color(Color::WHITE);
            gotoxy(1, 8); std::cout << "Riddle: " << question << "                    " << std::endl;
            gotoxy(1, 12); std::cout << "Your Answer: " << userInput << "_" << "                    " << std::endl;
            gotoxy(10, 15); set_text_color(Color::YELLOW);
            std::cout << message << "                    " << std::endl; set_text_color(Color::WHITE);
        }

        char c = 0;
        bool hasInput = false;

        if (inputSource) {
            hasInput = inputSource->hasInput(total_global_time, c);
        }

        if (!hasInput) {
            if (!isSilent)
                Sleep(50);
            continue;
        }

        if (c == KEY_ESC) { // ESC
            std::string logMsg = "RIDDLE_EVENT Q=\"" + question + "\" A=\"ESC\" RESULT=SKIPPED";
            logEvent(logMsg);
            inRiddle = false; solved = false;
        }
        else if (c == KEY_ENTER || c == KEY_ONE) { // ENTER or '1'
            bool isCorrect = riddle_manager.checkAnswer(ridx, userInput);

            std::string resultStr = isCorrect ? "CORRECT" : "WRONG";
            std::string logMsg = "RIDDLE_EVENT Q=\"" + question + "\" A=\"" + userInput + "\" RESULT=" + resultStr;
            logEvent(logMsg);

            if (isCorrect) {
                message = "CORRECT! The path opens.";

                if (!isSilent) {
                    gotoxy(10, 15); set_text_color(Color::GREEN);
                    std::cout << message << "                       " << std::endl;
                    Sleep(1000);
                }

                inRiddle = false; solved = true;
                last_riddle_index = -1;
            }
            else {
                message = "WRONG! Try again or ESC.";
                userInput = "";
            }
        }
        else if (c == KEY_BACKSPACE) { // BACKSPACE
            if (!userInput.empty()) userInput.pop_back();
        }
        else if (isalnum(c) || c == ' ') {
            userInput += c;
        }
    }

    if (inputSource) inputSource->setRiddleMode(false);

    //if (!isSilent)
    cls();

    return solved;
}

std::string game::getCurrentClue() const {
    if (last_riddle_index == -1) return "Find a riddle first to get a hint!";
    return riddle_manager.getClue(last_riddle_index);
}

void game::check_switches(Screen& screen) {
    int switchesOn = 0;
    for (int y = 0; y < Screen::MAX_Y; ++y) {
        for (int x = 0; x < Screen::MAX_X; ++x) {
            if (screen.getCharAt(Point(x, y, ' ')) == '\\') {
                switchesOn++;
            }
        }
    }
    for (const auto& doorCfg : activeSwitchDoors) {
        bool unlock = (switchesOn >= doorCfg.requiredSwitches);
        screen.setDoorUnlocked(doorCfg.x, doorCfg.y, unlock);
    }
}


game::~game() {
    if (inputSource) {
        delete inputSource;
        inputSource = nullptr;
    }
}


void game::logEvent(const std::string& eventDescription) {
    std::string logLine = std::to_string(total_global_time) + " " + eventDescription;
    resultsLog.push_back(logLine);
}



//after ex2
void game::loadLevelConfig(int levelIdx) {
    activeSwitchDoors.clear();
    isCurrentLevelDark = false;

    std::string filename = makeWorldFileName(levelIdx);
    std::ifstream file(filename);

    if (!file.is_open()) return;

    std::string line;
    int lineCounter = 0;

    while (std::getline(file, line)) {

        if (lineCounter < Screen::MAX_Y) {
            lineCounter++;
            continue; 
        }

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "DARK_ROOM") {
            isCurrentLevelDark = true;
        }
        else if (command == "DOOR_SWITCH") {
            SwitchDoorConfig cfg;
            ss >> cfg.x >> cfg.y >> cfg.requiredSwitches;
            activeSwitchDoors.push_back(cfg);
        }
    }
    file.close();
}