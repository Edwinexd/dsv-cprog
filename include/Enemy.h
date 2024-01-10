#ifndef ENEMY_H
#define ENEMY_H
#include <MultipartComponent.h>

class Enemy : public MultipartComponent
{
public:
    static std::shared_ptr<Enemy> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Enemy>(new Enemy(session, x, y, w, h, has_collision, d, hp, alive_image_path, dead_image_path));
    }
    void tick() override;
    virtual void kill() {
        hp = 0;
        dead = true;
        set_has_collision(false);
    }
    bool is_dead() {
        return dead;
    }
    virtual void damage(int amount) {
        hp -= amount;
        if (hp <= 0) {
            kill();
        }
    }
    int get_hp() {
        return hp;
    }
protected:
    Enemy(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_path, std::string dead_path);
private:
    int hp;
    int ticks_till_removal = 170;
    bool dead = false;
    void handle_death_tick();
};

#endif