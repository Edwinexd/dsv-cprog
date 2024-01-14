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