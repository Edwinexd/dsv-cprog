#include <Laser.h>
#include <MultipartRectangleTexture.h>
#include <Direction.h>
#include <Enemy.h>
#include <Spaceinvader.h>

Laser::Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) : MultipartComponent(session, x, y, w, h, has_collision), direction(direction), damage(damage) {
    addTexture(MultipartRectangleTexture::createInstance(session, w, h, {255, 0, 0, 255}));
    addTexture(MultipartRectangleTexture::createInstance(session, w, h, {200, 200, 200, 255}));
}

void Laser::tick() {
    std::cout << "Laser tick" << std::endl;
    rect.x += direction.dx;
    rect.y += direction.dy;
    ticks++;
    if (ticks % 32 == 0) {
        nextTexture();
    }
}

void Laser::on_collision(std::shared_ptr<Component> other) {
    std::cout << "Laser collided with something" << std::endl;
    rect.y = -10000;
    // cast other to enemy
    if (auto enemy = std::dynamic_pointer_cast<Spaceinvader>(other)) {
        enemy->damage(damage);
    }
}

