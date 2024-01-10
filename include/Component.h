#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
#include <memory>
#include "Session.h"

class Component : public std::enable_shared_from_this<Component>
{
public:
	// TODO: the following should be allowed to be set as lambdas via Component.onCollision = [](Component* other) { ... };
	virtual void on_collision(std::shared_ptr<Component> other) {}
	virtual void mouse_down(int x, int y) {}
	virtual void mouse_up(int x, int y) {}
	virtual void render() const = 0;
    SDL_Rect get_rect() const { return rect; }
	virtual void tick() = 0;
	bool has_collision() const { return collision; }
	void set_has_collision(bool c) { this->collision = c; }
	// std::shared_ptr<Component> getShared() { return shared_from_this(); }
	virtual ~Component() = default;
protected:
	Component(std::shared_ptr<Session>session, int x, int y, int w, int h, bool has_collision) : rect{ x,y,w,h }, session(session), collision(has_collision) {}
	SDL_Rect rect;
    std::shared_ptr<Session> session;
private:
	bool collision;
};

// TODO: Make IMGComponent, TextComponent, 
// (and some component that has multiple images that it can switch between) or one instance per texture that the user switches between


#endif
