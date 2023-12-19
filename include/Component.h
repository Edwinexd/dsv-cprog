#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
#include <memory>

class Component : public std::enable_shared_from_this<Component>
{
public:
	// TODO: the following should be allowed to be set as lambdas via Component.onCollision = [](Component* other) { ... };
	virtual void onCollision(Component* other) {};
	virtual void mouseDown(int x, int y) {}
	virtual void mouseUp(int x, int y) {}
	virtual void keyDown(SDL_Keycode key) {}
	virtual void keyUp(SDL_Keycode key) {}
	virtual void render() const = 0;
	SDL_Rect getRect() const { return rect; }
	virtual void tick() = 0;
	bool hasCollission() const { return has_collission; }
	void set_has_collision(bool has_collission) { this->has_collission = has_collission; }
	// std::shared_ptr<Component> getShared() { return shared_from_this(); }
protected:
	Component(int x, int y, int w, int h, bool has_collission) : rect{ x,y,w,h } {}
	SDL_Rect rect;
private:
	bool has_collission;
};

// TODO: Make IMGComponent, TextComponent, 
// (and some component that has multiple images that it can switch between) or one instance per texture that the user switches between


#endif
