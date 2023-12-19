#include <SDL2/SDL.h>
#include "Session.h"

void Session::add_component(std::shared_ptr<Component> comp)
{
    for(auto & component : this->components)
    {
        if(component == comp)
        {
            return;
        }
    }
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

void Session::unregister_key_event(std::shared_ptr<Component> src, int32_t key_code) {
    if(this->key_events.count(key_code) == 1) {
        auto vector = this->key_events.at(key_code);
        for (auto iter = vector.begin(); iter != vector.end(); iter++) {
            if (src == *iter) {
                vector.erase(iter);
            }

        }
    }

};

void Session::check_collision(std::shared_ptr<Component>& src) {
    //check if components' rects intersect
        for (auto& other_component : this->components) {
            if (src != other_component) //TODO: AND IF has_collision()
            {
                if (SDL_HasIntersection(src->get_rect(), &other_component->get_rect())) {
                    src->on_collision(other_component);
                }
            }
        }

}

void Session::play_sound(std::string path, int loops) {
    if(this->sound_bank.count(path) == 0)
    {
        this->sound_bank.insert(std::make_pair(path, std::unique_ptr<Mix_Chunk>(Mix_LoadWAV((constants::gResPath + path).c_str()))));
    }
    Mix_PlayChannel(-1, this->sound_bank.at(path).get(), loops);
}

void Session::run()
{
    bool exit = false;

    Uint32 tickInterval = 1000 / constants::FPS;
    Uint32 nextTick = SDL_GetTicks() + tickInterval;
    unsigned short counter = 0;
    while(!exit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit = true;
                    break;
                case SDL_KEYUP:
                    if(this->key_events.count(event.key.keysym.sym) == 1)
                    {
                        for(const auto& func : this->key_events.at(event.key.keysym.sym))
                        {
                            func(KeyPressType::UP);
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if(this->key_events.count(event.key.keysym.sym) == 1)
                    {
                        for(const auto& func : this->key_events.at(event.key.keysym.sym))
                        {
                            func(KeyPressType::DOWN);
                        }
                    }
                    break;
                case SDL_WINDOWEVENT:
                    switch(event.window.type)
                    {
                        case SDL_WINDOWEVENT_MOVED:
                            this->window_data.x = event.window.data1;
                            this->window_data.y = event.window.data2;
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            this->window_data.w = event.window.data1;
                            this->window_data.h = event.window.data2;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (std::shared_ptr<Component>& c : components)
                        c->mouseDown(event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    for (std::shared_ptr<Component>& c : components)
                        c->mouseUp(event.button.x, event.button.y);
                    break;
            }


        }
        for(auto & component : this->components)
        {
            component->tick();
            if(component->get_rect().x < 0 - 50|| component->get_rect().x > this->window_data.w + 50 || component->get_rect().y < 0 - 50 || component->get_rect().y > this->window_data.h + 50)
            {
                this->remove_component(component);
            }
            else {
                this->check_collision(component);  //TODO: IF has_collision()
            }
        }

        SDL_SetRenderDrawColor(this->ren, 255, 255, 255, 255);
        SDL_RenderClear(this->ren);
        for(auto & component : this->components)
        {
            component->render();
        }
        SDL_RenderPresent(this->ren);
        int delay = nextTick - SDL_GetTicks();
        if (delay > 0)
            SDL_Delay(delay);



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
			for (std::vector<std::shared_ptr<Component>>::iterator i = comps.begin();
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

		SDL_SetRenderDrawColor(sys.ren, 62, 62, 62, 255);
		SDL_RenderClear(sys.ren);
		for (std::shared_ptr<Component> c : comps)
			c->render();
		SDL_RenderPresent(sys.ren);

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
        counter++;
	}
}

void Session::play_sound(std::string path, int loops) {
    sys.play_sound(path, loops);
}
*/