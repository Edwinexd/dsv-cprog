#include <Player.h>
#include <Laser.h>

Player::Player(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_path, std::string dead_path) : Enemy(session, x, y, w, h, true, {0,0}, hp, alive_path, dead_path) {
    right_callback = [this](std::string key_pressed, KeyPressType t, Component& c) {
        if (is_dead()) {
            return;
        }
        if (t == KeyPressType::DOWN) {
            set_direction({3, 0, true});
        } else {
            if (get_direction().get_dx() > 0) {
                set_direction({0, 0});
            }
        }
    };

    left_callback = [this](std::string key_pressed, KeyPressType t, Component& c) {
        if (is_dead()) {
            return;
        }
        if (t == KeyPressType::DOWN) {
            set_direction({-3, 0, true});
        } else {
            if (get_direction().get_dx() < 0) {
                set_direction({0, 0});
            }
        }
    };
    
    shoot_callback = [this](std::string key_pressed, KeyPressType t, Component& c) {
        if (is_dead()) {
            return;
        }
        if (t == KeyPressType::DOWN) {
            this->shoot();
        }
    };

    session->register_key_event(KeyEventCallback({"Right", "D"}, right_callback, *this));
    session->register_key_event(KeyEventCallback({"Left", "A"}, left_callback, *this));
    session->register_key_event(KeyEventCallback("Space", shoot_callback, *this));
};

std::shared_ptr<Player> Player::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_image_path, std::string dead_image_path) {
    return std::shared_ptr<Player>(new Player(session, x, y, w, h, has_collision, hp, alive_image_path, dead_image_path));
}

void Player::tick() {
    Enemy::tick();
    if (is_dead()) {
        if (get_direction().get_dy() != 0 || get_direction().get_dx() != 0) {
            set_direction({0,0});
        }
        return;
    }

    if (ticks_since_last_shot < 120) {
        ticks_since_last_shot++;
    }
}

void Player::damage(int damage) {
    Enemy::damage(damage);
    get_session()->play_sound("sounds/explosion.wav", 0);
}

void Player::shoot() {
    if (ticks_since_last_shot < 120 || is_dead()) {
        return;
    }
    std::shared_ptr<Laser> b = Laser::create_instance(get_session(), get_x() + (get_width()/2), get_y() - get_height(), 5, 40, true, {0, -2}, 1);
    get_session()->add_component(b);
    ticks_since_last_shot = 0;
    get_session()->play_sound("sounds/laser_shoot.wav", 0);
}

void Player::kill() {
    Enemy::kill();
    get_session()->play_sound("sounds/big_explosion.wav", 0);
}