#include <SDL2/SDL.h>
#include <stdexcept>
#include "Session.h"
#include <iostream>

int count = 0;

void Session::add_component(std::shared_ptr<Component> comp)
{
    if (comp.get() == nullptr)
    {
        throw std::runtime_error("Component is nullptr");
    }
    for (auto component : this->components)
    {
        if (component == comp)
        {
            return;
        }
    }
    std::cout << "Adding component" << count << std::endl;
    count++;
    this->add_queue.push_back(comp);
}
void Session::remove_component(std::shared_ptr<Component> comp)
{

    this->remove_queue.push_back(comp);
}

void Session::remove_queued()
{
    for (auto &comp : this->remove_queue)
    {
        for (auto i = components.begin(); i != components.end();)
        {
            if (*i == comp)
            {
                i = components.erase(i);
            }
            else
            {
                i++;
            }
        }
    }
    this->remove_queue.clear();
}

void Session::add_queued()
{
    for (auto &comp : this->add_queue)
    {
        this->components.push_back(comp);
    }
    this->add_queue.clear();
}

void Session::register_key_event(KeyEventCallback callback)
{
    if (this->key_events.count(callback.getKeyCode() == 0))
    {
        this->key_events.insert(std::make_pair(callback.getKeyCode(), std::vector<KeyEventCallback>()));
    }
    this->key_events.at(callback.getKeyCode()).push_back(callback);
}

void Session::unregister_key_event(std::shared_ptr<Component> src)
{
    for (auto &key_event : this->key_events)
    {
        auto vector = key_event.second;
        for (auto iter = vector.begin(); iter != vector.end(); iter++)
        {
            if (src == *iter)
            {
                vector.erase(iter);
            }
        }
    }
}

void Session::unregister_key_event(std::shared_ptr<Component> src, int32_t key_code)
{
    if (this->key_events.count(key_code) == 1)
    {
        auto vector = this->key_events.at(key_code);
        for (auto iter = vector.begin(); iter != vector.end(); iter++)
        {
            if (src == *iter)
            {
                vector.erase(iter);
            }
        }
    }
};

void Session::check_collision(std::shared_ptr<Component> &src)
{
    // check if components' rects intersect
    for (auto &other_component : this->components)
    {
        if (src != other_component) // TODO: AND IF has_collision()
        {
            auto src_rect = src->get_rect();
            auto comp_rect = other_component->get_rect();
            if (SDL_HasIntersection(&src_rect, &comp_rect))
            {
                src->on_collision(other_component);
            }
        }
    }
}

void Session::play_sound(std::string path, int loops)
{
    sys.play_sound(path, loops);
}

void Session::run()
{
    bool exit = false;

    Uint32 tickInterval = 1000 / constants::FPS;
    unsigned short counter = 0;
    while (!exit)
    {
        Uint32 nextTick = SDL_GetTicks() + tickInterval;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit = true;
                break;
            case SDL_KEYUP:
                if (this->key_events.count(event.key.keysym.sym) == 1)
                {
                    for (const auto &func : this->key_events.at(event.key.keysym.sym))
                    {
                        func(KeyPressType::UP);
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (this->key_events.count(event.key.keysym.sym) == 1)
                {
                    for (const auto &func : this->key_events.at(event.key.keysym.sym))
                    {
                        func(KeyPressType::DOWN);
                    }
                }
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.type)
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
                for (std::shared_ptr<Component> &c : components)
                    c->mouseDown(event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                for (std::shared_ptr<Component> &c : components)
                    c->mouseUp(event.button.x, event.button.y);
                break;
            }
        }
        for (auto &component : this->components)
        {
            component->tick();
            if (component->get_rect().x < 0 - 50 || component->get_rect().x > this->window_data.w + 50 || component->get_rect().y < 0 - 50 || component->get_rect().y > this->window_data.h + 50)
            {
                this->remove_component(component);
            }
            else
            {
                this->check_collision(component); // TODO: IF has_collision()
            }
        }

        SDL_SetRenderDrawColor(this->ren, 255, 255, 255, 255);
        SDL_RenderClear(this->ren);
        for (auto &component : this->components)
        {
            component->render();
        }

        this->remove_queued();
        this->add_queued();
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
                if (c->get_rect().y <= -50) {
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