#include <Enemy.h>
#include <MultipartImageTexture.h>

Enemy::Enemy(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_path, std::string dead_path) : MultipartComponent(session, x, y, w, h, has_collision, d) {
    add_texture(MultipartImageTexture::create_instance(session, alive_path));
    add_texture(MultipartImageTexture::create_instance(session, dead_path));
    this->hp = hp;
}

std::shared_ptr<Enemy> Enemy::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_image_path, std::string dead_image_path) {
    return std::shared_ptr<Enemy>(new Enemy(session, x, y, w, h, has_collision, d, hp, alive_image_path, dead_image_path));
}

void Enemy::kill() {
    hp = 0;
    dead = true;
    set_has_collision(false);
}

void Enemy::damage(int amount) {
    hp -= amount;
    if (hp <= 0) {
        kill();
    }
}

void Enemy::tick() {
    MultipartComponent::tick();
    handle_death_tick();
}

void Enemy::handle_death_tick() {
    if (!dead) {
        return;
    }
    ticks_till_removal--;
    if (ticks_till_removal % 18 == 0) {
        set_texture((get_active_texture() + 1) % 2);
    }
    if (ticks_till_removal <= 0) {
        move_to(-10000, -10000);
    }
}