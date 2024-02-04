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
#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
#include <memory>
#include <Session.h>
#include <Direction.h>

// Spelmotorklass - grundläggande komponent som ska kunna renderas och röra sig
// Valt att lägga direction/rörelse direkt i Component istf e.x. MovementComponent för att undvika
// onödigt många subklasser till MultiPartComponent
class Component : public std::enable_shared_from_this<Component>
{
public:
	virtual void on_collision(std::shared_ptr<Component> other) {}
	// Event **must** be handled immediatly, as the component isn't guaranteed to exist after the function returns
	virtual void on_remove(std::shared_ptr<Component> other) {}
	virtual void mouse_down(int x, int y) {}
	virtual void mouse_up(int x, int y) {}
	virtual void render() const = 0;
	virtual void tick() {
		if (!direction.get_keep_on_screen() || (direction.get_dx() + rect.x > 0 && rect.x + direction.get_dx() < session->get_window_data().get_width() - rect.w)) {
			rect.x += direction.get_dx();
		}
		if (!direction.get_keep_on_screen() || (direction.get_dy() + rect.y > 0 && rect.y + direction.get_dy() < session->get_window_data().get_height() - rect.h)) {
			rect.y += direction.get_dy();
		}
	}
	bool has_collision() const { return collision; }
	void set_has_collision(bool c) { this->collision = c; }
	const Direction& get_direction() const { return direction; }
	void set_direction(const Direction& d) { direction = d; }
	void move(int dx, int dy) { rect.x += dx; rect.y += dy; }
	void move_to(int x, int y) { rect.x = x; rect.y = y; }
	int get_x() const { return rect.x; }
	int get_y() const { return rect.y; }
	int get_width() const { return rect.w; }
	int get_height() const { return rect.h; }
	void set_width(int w) { rect.w = w; }
	void set_height(int h) { rect.h = h; }
	virtual ~Component() = default;

	// Forbid value semantics
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(Component&&) = delete;
protected:
	Component(std::shared_ptr<Session>session, int x, int y, int w, int h, bool has_collision, Direction d = {0,0}) : session(session), collision(has_collision), rect{ x,y,w,h }, direction(d) {}
    SDL_Rect get_rect() const { return rect; }
	friend void Session::check_collision(std::shared_ptr<Component>); // Collision detection needs access to the rect
	std::shared_ptr<Session> get_session() const { return session; }
private:
    std::shared_ptr<Session> session;
	bool collision;
	SDL_Rect rect;
	Direction direction;
};

#endif
