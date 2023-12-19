#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include <vector>
#include <string>
#include <memory>

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

#endif