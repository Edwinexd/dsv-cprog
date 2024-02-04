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
#ifndef LASER_H
#define LASER_H
#include <MultipartComponent.h>
#include <Direction.h>

// Spelklass - en laser som rör sig i en riktning och gör skada på fiender vid kollision
class Laser : public MultipartComponent
{
public:
    static std::shared_ptr<Laser> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage);
    void tick() override;
    void on_collision(std::shared_ptr<Component> other) override;
    int getDamage() const {
        return damage;
    }
private:
    Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage);
    int damage;
    unsigned char ticks = 0;
};


#endif