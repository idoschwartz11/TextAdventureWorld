#pragma once

#include <iostream>
#include <string>
#include "Point.h"

using std::cout;
using std::endl;
using std::string;

class game; // Forward declaration

// 1st player inventory at (78,5)
// 2nd player inventory at (78,16)

class Screen {
public:
    enum { MAX_X = 80, MAX_Y = 25 };


private:
    game* activeGame = nullptr;
    string screen[MAX_Y] = {
        //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
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

    
            // -------------------  ROOM 1 MAP - THIS WILL BE THE DARK ROOM ---------------
    const std::string MAP_ROOM_1[Screen::MAX_Y] = {
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


    char getCharAtInternal(const Point& p) const {
        return screen[p.getY()][p.getX()];
    }

public:
    Screen();
    void setMap(const std::string map[MAX_Y]);

    char getCharAt(const Point& p) const { // Get character at point p
        return screen[p.getY()][p.getX()];
    }
    // Draw full static background (frame, HUD, etc.)
    //void drawBackground() const;
    void draw() const;

    void setCharAt(int x, int y, char c); // Set character at (x, y) to c

    void setP1Coins(int coins);
    void setP2Coins(int coins);

    void setP1Position(int px, int py);
    void setP2Position(int px, int py);


    bool isWall(const Point& p) const {
        return getCharAt(p) == 'W';
    }

    bool isSpring(const Point& p) const {
        return getCharAt(p) == '#';
    }

    bool isPlayer(const Point& p) const {
        char c = getCharAt(p);
        return (c == '$' || c == '&'); // Assuming '$' and '&' are player characters
    }

    bool is_secret_room(const Point& p) const {
        return getCharAt(p) == 'M';
    }


    // HUD helpers
    void setP1Inventory(char c) { setCharAt(77, 5, c); }
    void setP2Inventory(char c) { setCharAt(77, 16, c); }

    void activateBomb(int x, int y);

    void setGame(game* g) { activeGame = g; };

    void playerReadyToTransition(char playerChar);

    bool isOtherPlayerReady(char playerChar) const;

};
