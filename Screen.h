#pragma once

#include <iostream>
#include <string>
#include "Point.h"

using std::cout;
using std::endl;
using std::string;

class game; // Forward declaration
class Player;
// 1st player inventory at (78,5)
// 2nd player inventory at (78,16)

class Screen {
public:
    enum { MAX_X = 80, MAX_Y = 25 };


private:
    game* activeGame = nullptr;
    string screen[MAX_Y] = {
   //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W         WWWWWWWWWWWWWWWW  #    o     o            W              WKW|  P.I : |", // 1
    "W         W            o  W #                @      W              WWW| <3 x3  |", // 2
    "W   o     W   WWWWWWW     W # WWWWWWWWWWW         WWW   WWWWWWWWW    W|  o x00 |", // 3
    "WK        W   W     W     W   W       o W   o     W o   Woo     W    W|        |", // 4
    "W   WWWWWWW   W ooo W  o  W   W  o      W         W     Woo     W    W| Inv:   |", // 5
    "W   W     W   W ooo W     W   W      o  WWWWWWWWWWW  o  WWWWWWWWW    W|        |", // 6
    "W o W     W   W ooo W     W   W   o      o      o          o         W|        |", // 7
    "W   W     W   W     W     W   W           WWWWWWWWWWWWW            o W|  X=00  |", // 8
    "W1  W     W   WWWWWWW  o  W   WWWWWWWW o  W          o W             W|  Y=00  |", // 9
    "W                                         W   o        W         o   W|        |", // 10
    "W     o        WWWWWWWWWWWWWW      @      W      @     WWWWWWWWWWWWWWW|--------|", // 11
    "W              W            W             W o        o W   W       W1W|  P.II: |", // 12
    "W   WWWWWWWW   W   o        W   WWWWWWWWWWW          WWW   W   o   WWW| <3 x3  |", // 13
    "W   W      W   W       o    W   W          o   o        o  W        oW|  o x00 |", // 14
    "W o W  o   W   W                W   o   o                 WWWWWW     W|        |", // 15
    "W   W      W   WWWWWWWWWWWWWW   WWWWWWWWWWWWWWWWWWWWWWWWWWW    W    oW| Inv:   |", // 16
    "W   WWWWWWWW                 o                o           W    W     W|        |", // 17
    "W                o      o           o      o       o      W o  W     W|        |", // 18
    "W   o          WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W     W|        |", // 19
    "W         o    W                     o         o           WWWWWWWWWWW|  X=00  |", // 20
    "W   o          W   o             o                    o              W|  Y=00  |", // 21
    "W         o    W         o                  o      o                 W|        |", // 22
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWMWWWWWWWWW|        |", // 23
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|"  // 24
    };



    char getCharAtInternal(const Point& p) const {
            return screen[p.getY()][p.getX()];
        }

    bool isInHud(int x, int y) const;
    bool isVisibleFromPlayer(int x, int y, const Player& p) const;
    bool isCellVisible(int x, int y, const Player& p1, const Player& p2) const;

  

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

    void setP1Hearts(int hearts);
    void setP2Hearts(int hearts);

    void setP1Position(int px, int py);
    void setP2Position(int px, int py);

    void renderWithVisibility(const Player& p1, const Player& p2);
    void renderFull(const Player& p1, const Player& p2);

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
