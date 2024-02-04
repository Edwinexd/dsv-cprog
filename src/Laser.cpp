/* 
dsv-cprog-space-invaders - A space invaders inspired shooter written in C++ with SDL2
Copyright (C) 2024 Edwin Sundberg and Erik Lind Gou-Said

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <Laser.h>
#include <MultipartRectangleTexture.h>
#include <Direction.h>
#include <Enemy.h>
#include <Spaceinvader.h>

Laser::Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) : MultipartComponent(session, x, y, w, h, has_collision, direction), damage(damage) {
    add_texture(MultipartRectangleTexture::create_instance(session, w, h, {255, 0, 0, 255}));
    add_texture(MultipartRectangleTexture::create_instance(session, w, h, {200, 200, 200, 255}));
}

std::shared_ptr<Laser> Laser::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) {
    return std::shared_ptr<Laser>(new Laser(session, x, y, w, h, has_collision, direction, damage));
}

void Laser::tick() {
    MultipartComponent::tick();
    ticks++;
    if (ticks % 32 == 0) {
        next_texture();
    }
}

void Laser::on_collision(std::shared_ptr<Component> other) {
    move_to(-10000, -10000);
    if (auto enemy = std::dynamic_pointer_cast<Enemy>(other)) {
        enemy->damage(damage);
        get_session()->play_sound("sounds/hit.wav", 0);
    }
}

