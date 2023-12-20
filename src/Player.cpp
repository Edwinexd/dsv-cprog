#include <Player.h>

void Player::tick() {
    rect.x += direction.dx;
    rect.y += direction.dy;
}