#ifndef SPACEINVADER_H
#define SPACEINVADER_H
#include <Enemy.h>
#include <Laser.h>

class Spaceinvader : public Enemy
{
public:
    static std::shared_ptr<Spaceinvader> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Spaceinvader>(new Spaceinvader(session, x, y, w, h, hp, alive_image_path, dead_image_path));
    }
    void shoot() {
        std::shared_ptr<Laser> b = Laser::createInstance(session, get_rect().x + (get_rect().w/2), get_rect().y + get_rect().h, 5, 40, true, {0, 1}, 500);
        session->add_component(b);
    }
    void mouseDown(int x, int y) {
        shoot();
    }
protected:
    Spaceinvader(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_path, std::string dead_path) : Enemy(session, x, y, w, h, true, hp, alive_path, dead_path) {}
};


#endif