#include <Enemy.h>
#include <MultipartImageTexture.h>
#include <System.h>

Enemy::Enemy(int x, int y, int w, int h, bool has_collission, int hp, std::string alive_path, std::string dead_path) : MultipartComponent(x, y, w, h, has_collission) {
    addTexture(MultipartImageTexture::createInstance(alive_path));
    addTexture(MultipartImageTexture::createInstance(dead_path));
    this->hp = hp;
}

void Enemy::tick() {
    if (dead) {
        ticks_till_removal--;
        if (ticks_till_removal % 18 == 0) {
            nextTexture();
        }
        if (ticks_till_removal <= 0) {
            rect.y = -10000;
        }
    }
}