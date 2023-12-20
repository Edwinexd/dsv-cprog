#include<Spaceinvader.h>
#include <stdlib.h>

void Spaceinvader::shoot() {
    std::unique_ptr<Laser> b = Laser::createInstance(session, get_rect().x + (get_rect().w/2), get_rect().y + get_rect().h, 5, 40, true, {0, 1}, 500);
    session->add_component(std::move(b));
}

void Spaceinvader::tick() {
    handle_death_tick();
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
    if (ticks_loop % 2 == 0) {
        rect.x += directions[active_direction].dx;
        rect.y += directions[active_direction].dy;
    }
}