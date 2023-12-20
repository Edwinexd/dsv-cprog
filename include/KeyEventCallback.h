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
    std::vector<std::string> assigned_key;
    std::function<void(std::string , KeyPressType, Component&)> callback_fn;
    Component* target_comp;
public:

    KeyEventCallback(std::string n_key, std::function<void(std::string , KeyPressType, Component&)> n_cfn, Component& n_comp) : assigned_key(std::vector<std::string>()), callback_fn(std::move(n_cfn)), target_comp(&n_comp)
    {
        assigned_key.push_back(n_key);
    }

    KeyEventCallback(std::vector<std::string> n_key, std::function<void(std::string ,KeyPressType, Component&)> n_cfn, Component& n_comp) : assigned_key(n_key), callback_fn(std::move(n_cfn)), target_comp(&n_comp)
    {
    }

    KeyEventCallback(std::initializer_list<std::string> n_key, std::function<void(std::string ,KeyPressType, Component&)> n_cfn, Component& n_comp) : assigned_key(n_key), callback_fn(std::move(n_cfn)), target_comp(&n_comp)
    {
    }


    std::vector<int32_t> getKeyCode() const
    {
        std::vector<int32_t> ret;
        for(auto key : assigned_key)
        {
            ret.push_back(SDL_GetKeyFromName(key.c_str()));
        }
        return ret;
    }

    void operator()(int32_t key, KeyPressType press_type) const
    {

        callback_fn(SDL_GetKeyName(key), press_type, *target_comp);
    }

    Component& get_component() const
    {
        return *target_comp;
    }

    friend bool operator==(Component* lhs, const KeyEventCallback& rhs)
    {
        return lhs == rhs.target_comp;
    }


};

#endif


