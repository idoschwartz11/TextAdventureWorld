#include <iostream>
#include "Obstacle.h"


void Obstacle::translate(Direction dir) {
    int dx = 0, dy = 0;
    switch (dir) {
    case Direction::LEFT:  dx = -1; break;
    case Direction::RIGHT: dx = 1; break;
    case Direction::UP:    dy = -1; break;
    case Direction::DOWN:  dy = 1; break;
    default: return;
    }

    for (auto& c : cells)
        c.set(c.getX() + dx, c.getY() + dy);
}