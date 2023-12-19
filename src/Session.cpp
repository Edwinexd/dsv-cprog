#include <SDL2/SDL.h>
#include "Session.h"
void Session::add_component(std::shared_ptr<Component> comp)
{
	this->components.push_back(comp);
}
void Session::remove_component(std::shared_ptr<Component> comp)
{
    for(long i = 0; i < this->components.size(); i++)
    {
        if(comp == this->components.at(i))
        {
            this->components.erase(this->components.begin() + i);
        }
    }
}

void Session::register_key_event(KeyEventCallback callback) {
    if (this->key_events.count(callback.getKeyCode() == 0))
    {
        this->key_events.insert(std::make_pair(callback.getKeyCode() ,std::vector<KeyEventCallback>()));
    }
    this->key_events.at(callback.getKeyCode()).push_back(callback);
}

void Session::unregister_key_event(std::shared_ptr<Component> src) {
    for(auto & key_event : this->key_events)
    {
        auto vector = key_event.second;
        for(auto iter = vector.begin(); iter != vector.end(); iter++)
        {
            if(src == *iter)
            {
                vector.erase(iter);
            }

        }
    }

}

void Session::unregister_key_event(std::shared_ptr<Component> src, wlong key_code) {
    if(this->key_events.count(key_code) == 1) {
        auto vector = this->key_events.at(key_code);
        for (auto iter = vector.begin(); iter != vector.end(); iter++) {
            if (src == *iter) {
                vector.erase(iter);
            }

        }
    }

};

void Session::run()
{
    bool exit = 0;

    while(!quit)
    {

    }
}

/*

#define FPS 80

void Session::add(std::shared_ptr<Component> comp) {
	added.push_back(comp);
}

void Session::remove(std::shared_ptr<Component> comp) {
	removed.push_back(comp);
}

void Session::run() {
	bool quit = false;

	Uint32 tickInterval = 1000 / FPS;
    unsigned short counter = 0;
	while (!quit) {
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: quit = true; break;
			case SDL_MOUSEBUTTONDOWN:
				for (std::shared_ptr<Component> c : comps)
					c->mouseDown(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				for (std::shared_ptr<Component> c : comps)
					c->mouseUp(event.button.x, event.button.y);
				break;
			}
		}

		for (std::shared_ptr<Component> c : comps) {
			c->tick();
            if (counter % 100 == 0) {
                if (c->getRect().y <= -50) {
                    remove(c);
                }
            }
        }

		for (std::shared_ptr<Component> c : added)
			comps.push_back(c);
        
		added.clear();

		for (std::shared_ptr<Component> c : removed) {
			for (vector<std::shared_ptr<Component>>::iterator i = comps.begin();
				i != comps.end();)
			{
				if (*i == c) 
				{
					i = comps.erase(i);
				}
				else {
					i++;
				}
			}
		}
		removed.clear();

		SDL_SetRenderDrawColor(sys.ren, 255, 255, 255, 255);
		SDL_RenderClear(sys.ren);
		for (std::shared_ptr<Component> c : comps)
			c->render();
		SDL_RenderPresent(sys.ren);

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
}

void Session::play_sound(std::string path, int loops) {
    sys.play_sound(path, loops);
}
*/