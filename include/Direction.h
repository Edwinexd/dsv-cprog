#ifndef DIRECTION_H
#define DIRECTION_H

// Spelmotorklass - en riktning/rörelse/"velocity"
struct Direction
{
    Direction(int dx, int dy, bool keep_on_screen = false);
    int dx, dy;
    bool keep_on_screen;
    const Direction& operator+=(const Direction& other);
    const Direction& operator-=(const Direction& other);
    const Direction operator+(const Direction& other) const;
    const Direction operator-(const Direction& other) const;
};

#endif