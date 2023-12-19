#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include "KeyEventCallback.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>


class Session
{
private:
	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Component>> add_queue, remove_queue;
	std::unordered_map<unsigned long long, std::vector<KeyEventCallback>> key_events;
public:

	Session()
	{
		components = std::vector<std::shared_ptr<Component>>();
		add_queue = std::vector<std::shared_ptr<Component>>();
		remove_queue = std::vector<std::shared_ptr<Component>>();
		key_events = std::unordered_map<unsigned long long, std::vector<std::shared_ptr<void (unsigned long long)>>>();
	}



	void add_component(std::shared_ptr<Component> comp);
	void remove_component(std::shared_ptr<Component> comp);
	void register_key_event(KeyEventCallback callback);
	void unregister_key_event(std::shared_ptr<Component> src); // remove every callback from that component
	void unregister_key_event(std::shared_ptr<Component> src, wlong key_code);
	void tick_components();
	void check_collision();
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