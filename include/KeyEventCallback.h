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

// Spelmotorklass - Callback hantering för tangentbordstryckningar
class KeyEventCallback
{


private:
    std::vector<std::string> assigned_key;
    std::function<void(std::string , KeyPressType, Component&)> callback_fn;
    Component* target_comp;
    Component& get_component() const
    {
        return *target_comp;
    }
    friend void Session::unregister_key_event(Component*);
    friend void Session::unregister_key_event(Component*, int32_t);
public:

    KeyEventCallback(std::string n_key, std::function<void(std::string , KeyPressType, Component&)> n_cfn, Component& n_comp);

    KeyEventCallback(std::vector<std::string> n_key, std::function<void(std::string ,KeyPressType, Component&)> n_cfn, Component& n_comp);

    KeyEventCallback(std::initializer_list<std::string> n_key, std::function<void(std::string ,KeyPressType, Component&)> n_cfn, Component& n_comp);


    std::vector<int32_t> get_key_code() const;

    void operator()(int32_t key, KeyPressType press_type) const;

    bool operator==(Component* other) const
    {
        return target_comp == other;
    }
};

inline bool operator==(Component* lhs, const KeyEventCallback& rhs)
{
    return rhs == lhs;
}

#endif


