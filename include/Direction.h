#ifndef DIRECTION_H
#define DIRECTION_H

// Spelmotorklass - en riktning/rörelse/"velocity"
struct Direction
{
public:
    Direction(int dx, int dy, bool keep_on_screen = false);
    int get_dx() const { return dx; }
    int get_dy() const { return dy; }
    bool get_keep_on_screen() const { return keep_on_screen; }
    const Direction& operator+=(const Direction& other);
    const Direction& operator-=(const Direction& other);
    const Direction operator+(const Direction& other) const;
    const Direction operator-(const Direction& other) const;
private:
    int dx, dy;
    bool keep_on_screen;
};

#endif