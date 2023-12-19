#ifndef LASER_H
#define LASER_H
#include <MultipartComponent.h>
#include <Direction.h>

class Laser : public MultipartComponent
{
public:
    static std::shared_ptr<Laser> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage) {
        return std::shared_ptr<Laser>(new Laser(session, x, y, w, h, has_collision, direction, damage));
    }
    void tick() override;
    void on_collision(std::shared_ptr<Component> other) override;
    int getDamage() const {
        return damage;
    }
protected:
    Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage);
private:
    Direction direction;
    int damage;
    unsigned char ticks = 0;
};


#endif