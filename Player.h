#pragma once

#include "Point.h"
#include "Screen.h"
#include <cstring>

class Player {
    static constexpr int NUM_KEYS = 5;

    int x = 5;
    int y = 5;
    Point body;
    char ch;                 // '$' or '&'
    char keys[NUM_KEYS + 1]; // movement keys + stay
    Screen& screen;
    Player* other = nullptr;
    int hearts = 3;

    Direction currentDir = Direction::STAY;

    // coins and inventory
    int coins = 0;
    char item = ' ';         // '!', 'K', '@' or ' ' if empty

    // spring state
    bool inSpringCompress = false;
    Direction compressDir = Direction::STAY;
    int compressedCount = 0;

    bool inSpringLaunch = false;
    Direction springDir = Direction::STAY;
    int springSpeed = 0;
    int springTicksLeft = 0;

    // visual spring restore
    static constexpr int MAX_SPRING_LEN = 40;
    Point collapsedSpringCells[MAX_SPRING_LEN];
    int numCollapsedSpringCells = 0;
    bool restoringSpring = false;
    int restoreIndex = 0;
    int restoreDelayCounter = 0;

    void startSpringLaunch();
    Direction findWallDirForSpring(const Point& springPos) const;
    void springRestoreTick();

public:
    Player(const Point& p, char c, int startX, int startY,const char movKeys[], Screen& scr);

    Player(const Point& p, char c, const char movKeys[], Screen& scr);

    void setOther(Player* p) { other = p; }

    void draw();
    void move();
    void handleKeyPressed(char key);
    void dropItem();

    int getX() const { return x; }
    int getY() const { return y; }

    int  getCoins() const { return coins; }
    char getItem()  const { return item; }
    void resetPosition(int newX, int newY);
    int  getHearts() const { return hearts; }
    bool isDead()   const { return hearts <= 0; }
    void takeDamage(int dmg = 1);

    // Helpers from User 1
    int getDiffX() const { return body.getDiffX(); }
    int getDiffY() const { return body.getDiffY(); }

    // Logic from User 2 (Shop and Doors)
    bool tryToBuyItem(int itemX, int itemY);
    void setDoorUnlocked(int x, int y) { screen.setDoorUnlocked(x, y); }
};