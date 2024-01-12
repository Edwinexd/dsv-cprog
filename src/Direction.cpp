#include "Direction.h"

Direction::Direction(int dx, int dy, bool keep_on_screen) : dx(dx), dy(dy), keep_on_screen(keep_on_screen) {}

const Direction &Direction::operator+=(const Direction &other)
{
    dx += other.dx;
    dy += other.dy;
    return *this;
}

const Direction &Direction::operator-=(const Direction &other)
{
    dx -= other.dx;
    dy -= other.dy;
    return *this;
}

const Direction Direction::operator+(const Direction &other) const
{
    Direction temp(*this);
    temp += other;
    return temp;
}

const Direction Direction::operator-(const Direction &other) const
{
    Direction temp(*this);
    temp -= other;
    return temp;
}