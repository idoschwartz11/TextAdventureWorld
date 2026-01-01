#pragma once

#include <iostream>
#include "utils.h"
#include "Direction.h"

using std::cout;

class Point {
    int x = 1, y = 1;
    int diff_x = 1, diff_y = 0;
    char ch = '$';
public:
    Point() {} // Point with default values

    Point(int x1, int y1) { // Point with default direction and default char
        x = x1;
        y = y1;
        diff_x = 0;
        diff_y = 0;
        ch = '$';
    }

    Point(int x1, int y1, char c) { // Point with default direction and given char
        x = x1;
        y = y1;
        diff_x = 0;
        diff_y = 0;
        ch = c;
    }

    Point(int x1, int y1, int diffx, int diffy, char c) {
        x = x1;
        y = y1;
        diff_x = diffx;
        diff_y = diffy;
        ch = c;
    }

    void move();

    void setDirection(Direction dir);

    void draw() const {
        draw(ch);
    }

    void draw(char c) const {
        gotoxy(x, y);
        cout << c;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getDiffX() const {
        return diff_x;
    }

    int getDiffY() const {
        return diff_y;
    }

    void set(int newX, int newY) {
        x = newX;
        y = newY;
    }
};
