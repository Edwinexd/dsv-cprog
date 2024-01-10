#ifndef PLAYER_H
#define PLAYER_H
#include <MultipartComponent.h>
#include <Direction.h>
#include "MultipartRectangleTexture.h"
#include "Enemy.h"

// Spelklass - Player härleds från Enemy
class Player : public Enemy
{
public:
    static std::shared_ptr<Player> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_image_path, std::string dead_image_path);
    void tick() override;
    void shoot();
    void damage(int amount) override;
private:
    unsigned char ticks_since_last_shot = 0;

    std::function<void(std::string ,KeyPressType, Component&)> right_callback;
    std::function<void(std::string, KeyPressType, Component&)> left_callback;
    std::function<void(std::string, KeyPressType, Component&)> shoot_callback;

    Player(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_path, std::string dead_path);
};

#endif