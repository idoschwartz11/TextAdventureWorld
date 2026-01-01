#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Point.h"
#include "Color.h"

using std::cout;
using std::endl;
using std::string;

class game; // Forward declaration
class Player;

class Screen {
public:
    enum { MAX_X = 80, MAX_Y = 25 };
    enum { HUD_W = 20, HUD_H = 3 };

private:
    game* activeGame = nullptr;

    // HUD anchor (top-left) taken from 'L' in the .screen file.
    // If no 'L' exists in the file, defaults to (0,0).
    int legendRow = 0;
    int legendCol = 0;

    // Cached HUD state (so game can update via setters, and HUD is always rebuilt consistently).
    // Merged: Split coins to P1/P2 to support Shop logic
    int hudP1x = 0, hudP1y = 0;
    int hudP2x = 0, hudP2y = 0;
    int hudP1Hearts = 3;
    int hudP2Hearts = 3;
    int hudP1Coins = 0;
    int hudP2Coins = 0;
    int hudCoins = 0; // Legacy/Total backup
    int hudScore = 0;
    char hudP1Inv = ' ';
    char hudP2Inv = ' ';

    void rebuildHud();
    void writeHudLine(int rowOffset, const std::string& text);
    static std::string fitToHudWidth(std::string s);

    // Default map (will be overwritten by loadFromFile)
    string screen[MAX_Y] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|--------|", // 0
    "W         WWWWWWWWWWWWWWWW  #    o     o            W              WKW|  P.I : |", // 1
    "W         W            o  W #                @      W              WWW| <3 x3  |", // 2
    "W   o     W   WWWWWWW     W # WWWWWWWWWWW         WWW   WWWWWWWWW    W|  o x00 |", // 3
    "W         W   W     W     W   W       o W   o     W o   Woo     W    W|        |", // 4
    "W   WWWWWWW   W ooo W  o  W   W  o      W         W     Woo     W    W| Inv:   |", // 5
    "W   W     W   W ooo W     W   W      o  WWWWWWWWWWW  o  WWWWWWWWW    W|        |", // 6
    "W o W     W   W ooo W     W   W   o      o      o          o         W|        |", // 7
    "W   W     W   W     W     W   W           WWWWWWWWWWWWW            o W|  X=00  |", // 8
    "W   W     W   WWWWWWW  o  W   WWWWWWWW o  W          o W             W|  Y=00  |", // 9
    "W                                         W   o        W         o   W|        |", // 10
    "W     o   * WWWWWWWWWWWWWW      @      W      @     WWWWWWWWWWWWWWW|--------|", // 11
    "W              W            W             W o        o W   W       W1W|  P.II: |", // 12
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

    char getCharAtInternal(const Point& p) const {
            return screen[p.getY()][p.getX()];
    }

    bool isInHud(int x, int y) const;
    bool isVisibleFromPlayer(int x, int y, const Player& p) const;
    bool isCellVisible(int x, int y, const Player& p1, const Player& p2) const;

public:
    Screen();
    void setMap(const std::string map[MAX_Y]);

    // New (Ex2): load screen from a text file (adv-world*.screen)
    // Also detects 'L' and uses it as HUD anchor.
    bool loadFromFile(const std::string& filename);

    char getCharAt(const Point& p) const { 
        return screen[p.getY()][p.getX()];
    }
    
    void draw() const;

    void setCharAt(int x, int y, char c); 

    // HUD Data Setters
    void setCoins(int totalCoins); // Shared/Total
    void setP1Coins(int coins);    // User 2: Individual
    void setP2Coins(int coins);    // User 2: Individual
    
    void setScore(int score);

    void setP1Hearts(int hearts);
    void setP2Hearts(int hearts);

    void setP1Position(int px, int py);
    void setP2Position(int px, int py);
    
    void setP1Inventory(char c);
    void setP2Inventory(char c);

    // Rendering
    void renderWithVisibility(const Player& p1, const Player& p2);
    void renderFull(const Player& p1, const Player& p2);

    // Helpers
    bool isWall(const Point& p) const { return getCharAt(p) == 'W'; }
    bool isSpring(const Point& p) const { return getCharAt(p) == '#'; }
    bool isPlayer(const Point& p) const {
        char c = getCharAt(p);
        return (c == '$' || c == '&');
    }
    bool is_secret_room(const Point& p) const { return getCharAt(p) == 'M'; }
    bool isHudCell(int x, int y) const { return isInHud(x, y); }

    // Game Interactions
    void activateBomb(int x, int y);
    void setGame(game* g) { activeGame = g; };
    game* getGame() const { return activeGame; }

    // Doors & Transitions
    // Merged: Added destChar to support specific door linking
    void playerReadyToTransition(char playerChar, char destChar);
    void playerReadyToTransition(char playerChar) { playerReadyToTransition(playerChar, '0'); } // overload for compatibility
    bool isOtherPlayerReady(char playerChar) const;
    void setDoorUnlocked(int x, int y);

    // Colors
    void drawCharAt(int x, int y, char c);
    // Merged: Added x,y to support User 2's coordinate-based coloring
    Color get_object_color(int x, int y, char c) const;
    Color get_player_color(char playerChar) const;
    void set_text_color(Color color);
    bool is_heart_char(int x, int y, char c) const;

    // Shop & Riddles (User 2)
    bool is_shop_item(char c) const;
    void displayMessage(const std::string& msg);
    std::string getGameClue() const; 
    bool triggerRiddle();
};