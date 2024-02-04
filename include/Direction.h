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