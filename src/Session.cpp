#include <SDL2/SDL.h>
#include <stdexcept>
#include <Session.h>
#include <iostream>

Session::Session() : window_data(0, 0, 0, 0)
{
    components = std::vector<std::shared_ptr<Component>>();
    add_queue = std::vector<std::shared_ptr<Component>>();
    remove_queue = std::vector<std::shared_ptr<Component>>();
    collision_events_queue = std::vector<CollisionEvent>();
    key_events = std::unordered_map<int32_t, std::vector<KeyEventCallback>>();
    win = sys.get_window();
    ren = sys.get_renderer();
    int w, h, x, y;
    SDL_GetWindowSize(win, &w, &h);
    SDL_GetWindowPosition(win, &x, &y);
    window_data.set_width(w);
    window_data.set_height(h);
    window_data.set_x(x);
    window_data.set_y(y);
}

std::shared_ptr<Session> Session::create_instance()
{
    return std::shared_ptr<Session>(new Session());
}

void Session::add_component(std::shared_ptr<Component> comp)
{
    if (comp.get() == nullptr)
    {
        throw std::runtime_error("Component is nullptr");
    }
    // check that unique_ptr ownership is transferred
    for (auto &component : this->components)
    {
        if (component.get() == comp.get())
        {
            return;
        }
    }
    this->add_queue.push_back(comp);
}

void Session::remove_component(std::shared_ptr<Component> comp)
{
    this->remove_queue.push_back(comp);
}

void Session::remove_queued()
{
    // copy of remove queue to allow components to remove other components in their destructor
    auto remove_queue_frozen = this->remove_queue;
    remove_queue.clear();
    for (auto comp : remove_queue_frozen)
    {
        for (auto i = components.begin(); i != components.end();)
        {
            if (i->get() == comp.get())
            {
                for (auto &other : components)
                {
                    if (other.get() != comp.get())
                    {
                        other->on_remove(comp);
                    }
                }
                this->unregister_key_event(comp.get());
                i = components.erase(i);
            }
            else
            {
                i++;
            }
        }
    }
}

void Session::add_queued()
{
    // copy of add queue to allow components to add other components in their constructor
    auto add_queue_frozen = this->add_queue;
    add_queue.clear();
    for (auto &comp : add_queue_frozen)
    {
        this->components.push_back(comp);
    }
}

void Session::handle_collision_events()
{
    for (auto &event : this->collision_events_queue)
    {
        event.src->on_collision(event.other);
        event.other->on_collision(event.src);
    }
    this->collision_events_queue.clear();
}

void Session::register_key_event(KeyEventCallback callback)
{
    for (auto key : callback.get_key_code())
    {
        if (this->key_events.count(key) == 0)
        {
            this->key_events.insert(std::make_pair(key, std::vector<KeyEventCallback>()));
        }
        this->key_events.at(key).push_back(callback);
    }
}

void Session::unregister_key_event(Component *src)
{
    for (auto &key_event : this->key_events)
    {
        auto vector = key_event.second;
        for (auto iter = vector.begin(); iter != vector.end();)
        {
            if (&(iter->get_component()) == src)
            {
                iter = vector.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        this->key_events.at(key_event.first) = vector;
    }
}

void Session::unregister_key_event(Component *src, int32_t key_code)
{
    if (this->key_events.count(key_code) == 1)
    {
        auto vector = this->key_events.at(key_code);
        for (auto iter = vector.begin(); iter != vector.end();)
        {
            if (src == &(iter->get_component()))
            {
                iter = vector.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        this->key_events.at(key_code) = vector;
    }
};

void Session::check_collision(std::shared_ptr<Component> src)
{
    if (!src->has_collision())
    {
        return;
    }
    // check if components' rects intersect
    for (auto other_component : this->components)
    {
        if (other_component == src)
        {
            continue;
        }
        if (!other_component->has_collision())
        {
            continue;
        }
        auto src_rect = src->get_rect();
        auto comp_rect = other_component->get_rect();
        if (SDL_HasIntersection(&src_rect, &comp_rect))
        {
            if (std::find(this->collision_events_queue.begin(), this->collision_events_queue.end(), CollisionEvent(src, other_component)) == this->collision_events_queue.end())
            {
                this->collision_events_queue.push_back(CollisionEvent(src, other_component));
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
                        func(event.key.keysym.sym, KeyPressType::UP);
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (this->key_events.count(event.key.keysym.sym) == 1)
                {
                    for (const auto &func : this->key_events.at(event.key.keysym.sym))
                    {
                        func(event.key.keysym.sym, KeyPressType::DOWN);
                    }
                }
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.type)
                {
                case SDL_WINDOWEVENT_MOVED:
                    this->window_data.set_x(event.window.data1);
                    this->window_data.set_y(event.window.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    this->window_data.set_width(event.window.data1);
                    this->window_data.set_height(event.window.data2);
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (auto &c : this->components)
                    c->mouse_down(event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                for (auto &c : this->components)
                    c->mouse_up(event.button.x, event.button.y);
                break;
            }
        }
        for (auto &component : this->components)
        {
            component->tick();
            if (component->get_x() < 0 - 50 || component->get_x() > this->window_data.get_width()+ 50 || component->get_y() < 0 - 50 || component->get_y() > this->window_data.get_height() + 50)
            {
                this->remove_component(component);
            }
            else
            {
                this->check_collision(component); // Pass the raw pointer of the component
            }
        }
        this->handle_collision_events();
        SDL_SetRenderDrawColor(this->ren, 255, 255, 255, 255);
        SDL_RenderClear(this->ren);
        this->remove_queued();
        this->add_queued();
        for (auto &component : this->components)
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
                    c->mouse_down(event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                for (std::shared_ptr<Component> c : comps)
                    c->mouse_up(event.button.x, event.button.y);
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