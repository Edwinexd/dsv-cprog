#ifndef SESSION_H
#define SESSION_H


#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include "System.h"

class KeyEventCallback;
class Component;

struct WindowInformation
{
    int w, h, x, y;

    WindowInformation(int n_w, int n_h, int n_x, int n_y) : w(n_w), h(n_h), x(n_x), y(n_y)
    {}
};

class Session
{
private:
    SDL_Window* win;
    SDL_Renderer* ren;


    WindowInformation window_data;
	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Component>> add_queue;
	std::vector<std::shared_ptr<Component>> remove_queue;
	std::unordered_map<int32_t , std::vector<KeyEventCallback>> key_events;

    void remove_queued();
	void add_queued();
public:

	Session() : window_data(0,0,0,0)
	{
		components = std::vector<std::shared_ptr<Component>>();
		add_queue = std::vector<std::shared_ptr<Component>>();
		remove_queue = std::vector<std::shared_ptr<Component>>();
		key_events = std::unordered_map<int32_t , std::vector<KeyEventCallback>>();
		win = sys.win;
		ren = sys.ren;
        SDL_GetWindowSize(win, &window_data.w, &window_data.h);
        SDL_GetWindowPosition(win, &window_data.x, &window_data.y);
	}



	std::shared_ptr<Component> add_component(std::unique_ptr<Component> comp);
	void remove_component(std::shared_ptr<Component> comp);
	void register_key_event(KeyEventCallback callback);
	void unregister_key_event(Component* src); // remove every callback from that component
	void unregister_key_event(Component* src, int32_t key_code);
    WindowInformation get_window_data()
    {
        return window_data;
    }
	void check_collision(std::shared_ptr<Component> src);
	void run();
	void play_sound(std::string path, int loops);
};
#include "Component.h"
#include "KeyEventCallback.h"

/*
class Session
{
public:
	void add(std::shared_ptr<Component> comp);
	void remove(std::shared_ptr<Component> comp);
	void run();
	void play_sound(std::string path, int loops);
private:
	std::vector<std::shared_ptr<Component>> comps;
	std::vector<std::shared_ptr<Component>> added, removed;
};
*/
#endif