#ifndef SPACEINVADER_H
#define SPACEINVADER_H
#include <Enemy.h>
#include <Laser.h>

class Spaceinvader : public Enemy
{
public:
    static std::shared_ptr<Spaceinvader> createInstance(int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Spaceinvader>(new Spaceinvader(x, y, w, h, hp, alive_image_path, dead_image_path));
    }
    void shoot() {
        std::shared_ptr<Laser> b = Laser::createInstance(getRect().x + (getRect().w/2), getRect().y + getRect().h, 5, 40, true, {0, 1}, 10);
        ses.add(b);
    }
    void mouseDown(int x, int y) {
        shoot();
    }
protected:
    Spaceinvader(int x, int y, int w, int h, int hp, std::string alive_path, std::string dead_path) : Enemy(x, y, w, h, true, hp, alive_path, dead_path) {}
};


#endif