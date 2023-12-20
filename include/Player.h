#ifndef PLAYER_H
#define PLAYER_H
#include <MultipartComponent.h>
#include <Direction.h>
#include "MultipartRectangleTexture.h"
#include "Enemy.h"

class Player : public Enemy
{
public:
    static std::unique_ptr<Player> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::unique_ptr<Player>(new Player(session, x, y, w, h, has_collision, hp, alive_image_path, dead_image_path));
    }
    void tick() override;
    void shoot();
    // void on_collision(std::shared_ptr<Component> other) override;
    void on_key_event(KeyPressType t, std::string key) {
        if (t == KeyPressType::DOWN) {
            if (key == "Right") {
                direction = {3, 0};
            } else if (key == "Left") {
                direction = {-3, 0};
            }
        } else if (t == KeyPressType::UP) {
            if (key == "Right") {
                if (direction.dx > 0) {
                    direction = {0, 0};
                }
            } else if (key == "Left") {
                if (direction.dx < 0) {
                    direction = {0, 0};
                }
            }
            /*
            if (key == "Right") {
                direction = {1, 0};
            } else if (key == "Left") {
                direction = {-1, 0};
            }*/
        }
    
    }
    
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
    std::function<void(std::string ,KeyPressType, Component&)> left_callback = [this](std::string key_pressed ,KeyPressType t, Component& c) {
        if (t == KeyPressType::DOWN) {
            this->direction = {-3, 0};
        } else {
            if (this->direction.dx < 0) {
                this->direction = {0, 0};
            }
        }
    };

    Player(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_path, std::string dead_path) : Enemy(session, x, y, w, h, true, hp, alive_path, dead_path) {
        session->register_key_event(KeyEventCallback(std::string("Right"), right_callback, *this));
        session->register_key_event(KeyEventCallback(std::string("Left"), left_callback, *this));
    };
};

#endif