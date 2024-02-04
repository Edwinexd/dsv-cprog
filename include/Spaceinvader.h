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
#ifndef SPACEINVADER_H
#define SPACEINVADER_H
#include <Enemy.h>
#include <Laser.h>

// Spelklass - Spaceinvader härleds från Enemy
class Spaceinvader : public Enemy
{
public:
    static std::shared_ptr<Spaceinvader> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Spaceinvader>(new Spaceinvader(session, x, y, w, h, hp, alive_image_path, dead_image_path));
    }
    void shoot();
    
private:
    Spaceinvader(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_path, std::string dead_path) : Enemy(session, x, y, w, h, true, {0,0}, hp, alive_path, dead_path) {}
};


#endif