#ifndef SPACEINVADER_H
#define SPACEINVADER_H
#include <Enemy.h>
#include <Laser.h>

class Spaceinvader : public Enemy
{
public:
    static std::unique_ptr<Spaceinvader> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path, unsigned int random_seed) {
        return std::unique_ptr<Spaceinvader>(new Spaceinvader(session, x, y, w, h, hp, alive_image_path, dead_image_path, random_seed));
    }
    void shoot();
    void tick() override;
    void mouseDown(int x, int y) {
        shoot();
    }
protected:
    Spaceinvader(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_path, std::string dead_path, unsigned int random_seed) : Enemy(session, x, y, w, h, true, hp, alive_path, dead_path), random_seed(random_seed) {}
private:
    unsigned int random_seed;
    unsigned int ticks_loop = 0;
    unsigned int active_direction = 0;
    // vector of Direction objects
    std::vector<Direction> directions = {{1, 0}, {-1, 0}, {1, 0}, {-1, 0}, {2, 0}, {-2, 0}};
};


#endif