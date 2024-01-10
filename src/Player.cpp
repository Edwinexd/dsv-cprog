#include <Player.h>
#include <Laser.h>

void Player::tick() {
    Enemy::tick();
    if (is_dead()) {
        if (get_direction().dy != 0 || get_direction().dx != 0) {
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
    session->play_sound("sounds/explosion.wav", 0);
}

void Player::shoot() {
    if (ticks_since_last_shot < 120 || is_dead()) {
        return;
    }
    std::shared_ptr<Laser> b = Laser::create_instance(session, get_x() + (get_width()/2), get_y() - get_height(), 5, 40, true, {0, -2}, 1);
    session->add_component(b);
    ticks_since_last_shot = 0;
    session->play_sound("sounds/laser_shoot.wav", 0);
}