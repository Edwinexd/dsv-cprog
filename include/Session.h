#ifndef SESSION_H
#define SESSION_H


#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include <System.h>

class KeyEventCallback;
class Component;

struct WindowInformation
{
	int get_width() const
	{
		return w;
	}
	int get_height() const
	{
		return h;
	}
	int get_x() const
	{
		return x;
	}
	int get_y() const
	{
		return y;
	}
	void set_width(int n_w)
	{
		w = n_w;
	}
	void set_height(int n_h)
	{
		h = n_h;
	}
	void set_x(int n_x)
	{
		x = n_x;
	}
	void set_y(int n_y)
	{
		y = n_y;
	}
    WindowInformation(int n_w, int n_h, int n_x, int n_y) : w(n_w), h(n_h), x(n_x), y(n_y)
    {}
private:
    int w, h, x, y;
};

struct CollisionEvent
{
	bool operator==(const CollisionEvent& other) const
	{
		return (src == other.src && this->other == other.other) || (src == other.other && this->other == other.src);
	}
	std::shared_ptr<Component> get_src() const
	{
		return src;
	}
	std::shared_ptr<Component> get_other() const
	{
		return other;
	}
private:
    CollisionEvent(std::shared_ptr<Component> src, std::shared_ptr<Component> other) : src(src), other(other)
    {
    } // only Session should be allowed to create this
    std::shared_ptr<Component> src;
    std::shared_ptr<Component> other;
	friend class Session;
};

// Spelmotorklass - Huvudklassen som håller koll, tickar och renderar komponenter
class Session
{
private:
    SDL_Window* win;
    SDL_Renderer* ren;


	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Component>> add_queue;
	std::vector<std::shared_ptr<Component>> remove_queue;
	std::vector<CollisionEvent> collision_events_queue;
	std::unordered_map<int32_t , std::vector<KeyEventCallback>> key_events;
    WindowInformation window_data;

    void remove_queued();
	void add_queued();
	void handle_collision_events();
	Session();
public:
	static std::shared_ptr<Session> create_instance();
	void add_component(std::shared_ptr<Component> comp);
	void remove_component(std::shared_ptr<Component> comp);
	void register_key_event(KeyEventCallback callback);
	void unregister_key_event(Component* src); // remove every callback from that component
	void unregister_key_event(Component* src, int32_t key_code);
    const WindowInformation& get_window_data()
    {
        return window_data;
    }
	void check_collision(std::shared_ptr<Component> src);
	void run();
	void play_sound(std::string path, int loops);
};
#include "Component.h"
#include "KeyEventCallback.h"

#endif