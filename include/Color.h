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