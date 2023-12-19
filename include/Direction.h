#ifndef DIRECTION_H
#define DIRECTION_H

struct Direction
{
    Direction(int dx, int dy) : dx(dx), dy(dy) {}
    int dx, dy;
};

#endif