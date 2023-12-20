#ifndef DIRECTION_H
#define DIRECTION_H

struct Direction
{
    Direction(int dx, int dy) : dx(dx), dy(dy) {}
    int dx, dy;
    const Direction& operator+=(const Direction& other) {
        dx += other.dx;
        dy += other.dy;
        return *this;
    }
    const Direction& operator-=(const Direction& other) {
        dx -= other.dx;
        dy -= other.dy;
        return *this;
    }
    const Direction operator+(const Direction& other) const {
        Direction temp(*this);
        temp += other;
        return temp;
    }
};

#endif