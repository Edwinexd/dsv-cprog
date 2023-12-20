#include<Spaceinvader.h>

void Spaceinvader::shoot() {
    std::unique_ptr<Laser> b = Laser::createInstance(session, get_rect().x + (get_rect().w/2), get_rect().y + get_rect().h, 5, 40, true, {0, 1}, 500);
    session->add_component(std::move(b));
}