#ifndef KEYEVENTCALLBACK_H
#define KEYEVENTCALLBACK_H
#include "Component.h"
#include "Constants.h"
#include <memory>
#include <utility>
#include <functional>


enum KeyPressType{
    DOWN,
    UP
};

class Component;

class KeyEventCallback
{


private:
    std::string assigned_key;
    std::function<void(KeyPressType, std::shared_ptr<Component>)> callback_fn;
    std::shared_ptr<Component> target_comp;
public:

    KeyEventCallback(std::string n_key, std::function<void(KeyPressType, std::shared_ptr<Component>)> n_cfn, std::shared_ptr<Component> n_comp) : assigned_key(n_key), callback_fn(std::move(n_cfn)), target_comp(n_comp)
    {}

    int32_t getKeyCode() const
    {
        return SDL_GetKeyFromName(assigned_key.c_str());
    }

    void operator()(KeyPressType press_type) const
    {
        callback_fn(press_type, target_comp);
    }

    std::shared_ptr<Component> get_component() const
    {
        return target_comp;
    }

    friend bool operator==(Component* lhs, const KeyEventCallback& rhs)
    {
        return lhs == rhs.target_comp.get();
    }

};

#endif


