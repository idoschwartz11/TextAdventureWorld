#pragma once
#include <vector>
#include <stack>
#include "Point.h"
#include "Direction.h"

using std::vector;

class Obstacle {
public:
    using Cell = Point;
    vector<Cell> cells;

    Obstacle() = default;

    Obstacle(const vector<Cell>& obstacleCells)
        : cells(obstacleCells) {
    }

    int getWeight() const {
        return (int)cells.size();
    }

    const vector<Cell>& getCells() const {
        return cells;
    }

    bool occupies(int x, int y) const {
        for (const auto& c : cells)
            if (c.getX() == x && c.getY() == y)
                return true;
        return false;
    }

    void draw() const {
        for (const auto& c : cells)
            c.draw('*');
    }

    void erase() const {
        for (const auto& c : cells)
            c.draw(' ');
    }

    void translate(Direction dir);


private:
};

