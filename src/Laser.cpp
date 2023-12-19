#include <Laser.h>
#include <MultipartRectangleTexture.h>
#include <Direction.h>

Laser::Laser(int x, int y, int w, int h, bool has_collission, Direction direction, int damage) : MultipartComponent(x, y, w, h, has_collission), direction(direction), damage(damage) {
    addTexture(MultipartRectangleTexture::createInstance(w, h, {255, 0, 0, 255}));
    addTexture(MultipartRectangleTexture::createInstance(w, h, {200, 200, 200, 255}));
}

void Laser::tick() {
    rect.x += direction.dx;
    rect.y += direction.dy;
    ticks++;
    if (ticks % 32 == 0) {
        nextTexture();
    }
}

