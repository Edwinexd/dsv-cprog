#ifndef LASER_H
#define LASER_H
#include <MultipartComponent.h>
#include <Direction.h>

// Spelklass - en laser som rör sig i en riktning och gör skada på fiender vid kollision
class Laser : public MultipartComponent
{
public:
    static std::shared_ptr<Laser> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage);
    void tick() override;
    void on_collision(std::shared_ptr<Component> other) override;
    int getDamage() const {
        return damage;
    }
protected:
    Laser(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction direction, int damage);
private:
    int damage;
    unsigned char ticks = 0;
};


#endif