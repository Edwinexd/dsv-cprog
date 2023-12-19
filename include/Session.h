#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include "KeyEventCallback.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include "System.h"
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
	std::vector<std::shared_ptr<Component>> add_queue, remove_queue;
	std::unordered_map<int32_t , std::vector<KeyEventCallback>> key_events;
public:

	Session(WindowInformation n_win_info) : window_data(n_win_info)
	{
		components = std::vector<std::shared_ptr<Component>>();
		add_queue = std::vector<std::shared_ptr<Component>>();
		remove_queue = std::vector<std::shared_ptr<Component>>();
		key_events = std::unordered_map<int32_t , std::vector<KeyEventCallback>>();
		win = sys.win;
		ren = sys.ren;
	}



	void add_component(std::shared_ptr<Component> comp);
	void remove_component(std::shared_ptr<Component> comp);
	void register_key_event(KeyEventCallback callback);
	void unregister_key_event(std::shared_ptr<Component> src); // remove every callback from that component
	void unregister_key_event(std::shared_ptr<Component> src, int32_t key_code);
    WindowInformation get_window_data()
    {
        return window_data;
    }
	void check_collision(std::shared_ptr<Component>& src);
	void run();
	void play_sound(std::string path, int loops);
};

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