/* 
dsv-cprog-space-invaders - A space invaders inspired shooter written in C++ with SDL2
Copyright (C) 2024 Edwin Sundberg and Erik Lind Gou-Said

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef KEYEVENTCALLBACK_H
#define KEYEVENTCALLBACK_H
#include <Component.h>
#include <Constants.h>
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


