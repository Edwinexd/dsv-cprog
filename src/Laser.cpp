#include <Laser.h>
#include <MultipartRectangleTexture.h>
#include <Direction.h>

Laser::Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) : MultipartComponent(session, x, y, w, h, has_collision), direction(direction), damage(damage) {
    addTexture(MultipartRectangleTexture::createInstance(session, w, h, {255, 0, 0, 255}));
    addTexture(MultipartRectangleTexture::createInstance(session, w, h, {200, 200, 200, 255}));
}

void Laser::tick() {
    rect.x += direction.dx;
    rect.y += direction.dy;
    ticks++;
    if (ticks % 32 == 0) {
        nextTexture();
    }
}

