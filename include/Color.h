#ifndef COLOR_H
#define COLOR_H

struct Color
{
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
    unsigned char r, g, b, a;
};

#endif