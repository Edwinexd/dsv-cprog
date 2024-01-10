#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
#include <memory>
#include "Session.h"
#include "Direction.h"

// Spelmotorklass - grundläggande komponent som ska kunna renderas och röra sig
// Valt att lägga direction/rörelse direkt i Component istf e.x. MovementComponent för att undvika
// onödigt många subklasser till MultiPartComponent
class Component : public std::enable_shared_from_this<Component>
{
public:
	virtual void on_collision(std::shared_ptr<Component> other) {}
	// Event **must** be handled immediatly, as the component will not be guaranteed to exist after the function returns
	virtual void on_remove(std::shared_ptr<Component> other) {}
	virtual void mouse_down(int x, int y) {}
	virtual void mouse_up(int x, int y) {}
	virtual void render() const = 0;
	virtual void tick() {
		if (!direction.keep_on_screen || (direction.dx + rect.x > 0 && rect.x + direction.dx < session->get_window_data().w - rect.w)) {
			rect.x += direction.dx;
		}
		if (!direction.keep_on_screen || (direction.dy + rect.y > 0 && rect.y + direction.dy < session->get_window_data().h - rect.h)) {
			rect.y += direction.dy;
		}
	}
	bool has_collision() const { return collision; }
	void set_has_collision(bool c) { this->collision = c; }
	Direction get_direction() const { return direction; }
	void set_direction(Direction d) { direction = d; }
	void move(int dx, int dy) { rect.x += dx; rect.y += dy; }
	void move_to(int x, int y) { rect.x = x; rect.y = y; }
	int get_x() const { return rect.x; }
	int get_y() const { return rect.y; }
	int get_width() const { return rect.w; }
	int get_height() const { return rect.h; }
	void set_width(int w) { rect.w = w; }
	void set_height(int h) { rect.h = h; }
	virtual ~Component() = default;
protected:
	Component(std::shared_ptr<Session>session, int x, int y, int w, int h, bool has_collision, Direction d = {0,0}) : session(session), collision(has_collision), rect{ x,y,w,h }, direction(d) {}
    std::shared_ptr<Session> session;
    SDL_Rect get_rect() const { return rect; }
	friend void Session::check_collision(std::shared_ptr<Component>); // Collision detection needs access to the rect
private:
	bool collision;
	SDL_Rect rect;
	Direction direction;
};

#endif
