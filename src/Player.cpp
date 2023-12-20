#include <Player.h>

void Player::tick() {
    handle_death_tick();
    rect.x += direction.dx;
    rect.y += direction.dy;
}