#ifndef ENEMY_H
#define ENEMY_H
#include <MultipartComponent.h>

// Spelmotorklass - ett objekt som kan skadas och "dö", härleds från MultipartComponent
class Enemy : public MultipartComponent
{
public:
    static std::shared_ptr<Enemy> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_image_path, std::string dead_image_path);
    void tick() override;
    virtual void kill();
    bool is_dead() const {
        return dead;
    }
    virtual void damage(int amount);
    int get_hp() const {
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