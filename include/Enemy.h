#ifndef ENEMY_H
#define ENEMY_H
#include <MultipartComponent.h>

class Enemy : public MultipartComponent
{
public:
    static std::shared_ptr<Enemy> createInstance(int x, int y, int w, int h, bool has_collission, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Enemy>(new Enemy(x, y, w, h, has_collission, hp, alive_image_path, dead_image_path));
    }
    void tick() override;
    void kill() {
        hp = 0;
        dead = true;
        set_has_collision(false);
    }
    bool is_dead() {
        return dead;
    }
    void damage(int amount) {
        hp -= amount;
        if (hp <= 0) {
            kill();
        }
    }
protected:
    Enemy(int x, int y, int w, int h, bool has_collission, int hp, std::string alive_path, std::string dead_path);
private:
    int hp;
    int ticks_till_removal = 170;
    bool dead = false;
};

#endif