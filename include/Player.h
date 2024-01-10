#ifndef PLAYER_H
#define PLAYER_H
#include <MultipartComponent.h>
#include <Direction.h>
#include "MultipartRectangleTexture.h"
#include "Enemy.h"

class Player : public Enemy
{
public:
    static std::unique_ptr<Player> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::unique_ptr<Player>(new Player(session, x, y, w, h, has_collision, hp, alive_image_path, dead_image_path));
    }
    void tick() override;
    void shoot();
    // void on_collision(std::shared_ptr<Component> other) override;
private:
    Direction direction = {0, 0};
    unsigned char ticks_since_last_shot = 0;

    std::function<void(std::string ,KeyPressType, Component&)> right_callback = [this](std::string key_pressed,KeyPressType t, Component& c) {
        if (t == KeyPressType::DOWN) {
            this->direction = {3, 0};
        } else {
            if (this->direction.dx > 0) {
                this->direction = {0, 0};
            }
        }
    };
    std::function<void(std::string, KeyPressType, Component&)> left_callback = [this](std::string key_pressed ,KeyPressType t, Component& c) {
        if (t == KeyPressType::DOWN) {
            this->direction = {-3, 0};
        } else {
            if (this->direction.dx < 0) {
                this->direction = {0, 0};
            }
        }
    };
    std::function<void(std::string, KeyPressType, Component&)> shoot_callback = [this](std::string key_pressed, KeyPressType t, Component& c) {
        if (t == KeyPressType::DOWN) {
            this->shoot();
        }
    };

    Player(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_path, std::string dead_path) : Enemy(session, x, y, w, h, true, hp, alive_path, dead_path) {
        session->register_key_event(KeyEventCallback({"Right", "D"}, right_callback, *this));
        session->register_key_event(KeyEventCallback({"Left", "A"}, left_callback, *this));
        session->register_key_event(KeyEventCallback("Space", shoot_callback, *this));
    };
};

#endif