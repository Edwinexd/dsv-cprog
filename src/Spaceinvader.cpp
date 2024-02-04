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
#include <stdlib.h>
#include <Spaceinvader.h>

void Spaceinvader::shoot() {
    std::shared_ptr<Laser> b = Laser::create_instance(get_session(), get_x() + (get_width()/2), get_y() + get_height(), 5, 40, true, {0, 2}, 1);
    get_session()->add_component(b);
}


/*
void Spaceinvader::tick() {
    Enemy::tick();
    ticks_loop++;
    // For every n ticks, move in a random direction for n ticks
    // after n ticks, move in the opposite direction for n ticks
    // they are synced in the vector so that 0 - 1 reverse each other and 2 - 3 reverse each other
    if (ticks_loop % 100 == 0) {
        if (ticks_loop % 200 == 0) {
            // reverse direction, if active_direction is even we add 1, if it is odd we subtract 1
            active_direction = (active_direction % 2 == 0) ? active_direction + 1 : active_direction - 1;
        } else {
            srand(random_seed + ticks_loop);
            active_direction = rand() % directions.size();
        }
    }
    set_direction(directions[active_direction]);
    if (ticks_loop % 2 == 0) {
        rect.x += directions[active_direction].dx;
        rect.y += directions[active_direction].dy;
    }
    */