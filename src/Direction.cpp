/* 
dsv-cprog-space-invaders - A space invaders inspired shooter written in C++ with SDL2
Copyright (C) 2024 Edwin Sundberg and Erik Lind Gou-Said

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <Direction.h>

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