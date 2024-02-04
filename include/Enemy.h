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
#ifndef ENEMY_H
#define ENEMY_H
#include <MultipartComponent.h>

// Spelmotorklass - ett objekt som kan skadas och "dö", härleds från MultipartComponent
class Enemy : public MultipartComponent
{
public:
    static std::shared_ptr<Enemy> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_image_path, std::string dead_image_path);
    void tick() override;
    virtual void kill();
    bool is_dead() const {
        return dead;
    }
    virtual void damage(int amount);
    int get_hp() const {
        return hp;
    }
protected:
    Enemy(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d, int hp, std::string alive_path, std::string dead_path);
private:
    int hp;
    int ticks_till_removal = 170;
    bool dead = false;
    void handle_death_tick();
};

#endif