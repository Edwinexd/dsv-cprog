#include <Laser.h>
#include <MultipartRectangleTexture.h>
#include <Direction.h>
#include <Enemy.h>
#include <Spaceinvader.h>

Laser::Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) : MultipartComponent(session, x, y, w, h, has_collision, direction), damage(damage) {
    add_texture(MultipartRectangleTexture::create_instance(session, w, h, {255, 0, 0, 255}));
    add_texture(MultipartRectangleTexture::create_instance(session, w, h, {200, 200, 200, 255}));
}

std::shared_ptr<Laser> Laser::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) {
    return std::shared_ptr<Laser>(new Laser(session, x, y, w, h, has_collision, direction, damage));
}

void Laser::tick() {
    MultipartComponent::tick();
    ticks++;
    if (ticks % 32 == 0) {
        next_texture();
    }
}

void Laser::on_collision(std::shared_ptr<Component> other) {
    move_to(-10000, -10000);
    if (auto enemy = std::dynamic_pointer_cast<Enemy>(other)) {
        enemy->damage(damage);
        session->play_sound("sounds/hit.wav", 0);
    }
}

