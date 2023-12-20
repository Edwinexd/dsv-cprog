#include <Player.h>
#include <Laser.h>

void Player::tick() {
    handle_death_tick();
    if (is_dead()) {
        return;
    }
    if (direction.dx + rect.x > 0 && rect.x + direction.dx < 850 - rect.w) {
        rect.x += direction.dx;
    }
    // rect.x += direction.dx;
    rect.y += direction.dy;
    if (ticks_since_last_shot < 120) {
        ticks_since_last_shot++;
    }
}

void Player::shoot() {
    if (ticks_since_last_shot < 120 || is_dead()) {
        return;
    }
    std::unique_ptr<Laser> b = Laser::createInstance(session, get_rect().x + (get_rect().w/2), get_rect().y - get_rect().h, 5, 40, true, {0, -1}, 500);
    session->add_component(std::move(b));
    ticks_since_last_shot = 0;
}