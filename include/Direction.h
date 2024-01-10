#ifndef DIRECTION_H
#define DIRECTION_H

struct Direction
{
    Direction(int dx, int dy, bool keep_on_screen = false) : dx(dx), dy(dy), keep_on_screen(keep_on_screen) {}
    int dx, dy;
    bool keep_on_screen;
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