#include <Enemy.h>
#include <MultipartImageTexture.h>

Enemy::Enemy(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_path, std::string dead_path) : MultipartComponent(session, x, y, w, h, has_collision) {
    addTexture(MultipartImageTexture::createInstance(session, alive_path));
    addTexture(MultipartImageTexture::createInstance(session, dead_path));
    this->hp = hp;
}

void Enemy::tick() {
    handle_death_tick();
}

void Enemy::handle_death_tick() {
    if (!dead) {
        return;
    }
    ticks_till_removal--;
    if (ticks_till_removal % 18 == 0) {
        setTexture((getActiveTexture() + 1) % 2);
    }
    if (ticks_till_removal <= 0) {
        rect.y = -10000;
    }
}