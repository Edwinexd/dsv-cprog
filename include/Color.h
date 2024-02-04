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
#ifndef COLOR_H
#define COLOR_H

// Spelmotorklass - abstraktion för en färg
struct Color
{
public:
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
    unsigned char get_r() const { return r; }
    unsigned char get_g() const { return g; }
    unsigned char get_b() const { return b; }
    unsigned char get_a() const { return a; }
private:
    unsigned char r, g, b, a;
};

#endif