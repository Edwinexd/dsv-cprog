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
#include <KeyEventCallback.h>

KeyEventCallback::KeyEventCallback(std::string n_key, std::function<void(std::string, KeyPressType, Component &)> n_cfn, Component &n_comp) : assigned_key(std::vector<std::string>()), callback_fn(std::move(n_cfn)), target_comp(&n_comp)
{
    assigned_key.push_back(n_key);
}

KeyEventCallback::KeyEventCallback(std::vector<std::string> n_key, std::function<void(std::string, KeyPressType, Component &)> n_cfn, Component &n_comp) : assigned_key(n_key), callback_fn(std::move(n_cfn)), target_comp(&n_comp)
{
}

KeyEventCallback::KeyEventCallback(std::initializer_list<std::string> n_key, std::function<void(std::string, KeyPressType, Component &)> n_cfn, Component &n_comp) : assigned_key(n_key), callback_fn(std::move(n_cfn)), target_comp(&n_comp)
{
}

std::vector<int32_t> KeyEventCallback::get_key_code() const
{
    std::vector<int32_t> ret;
    for(auto key : assigned_key)
    {
        ret.push_back(SDL_GetKeyFromName(key.c_str()));
    }
    return ret;
}

void KeyEventCallback::operator()(int32_t key, KeyPressType press_type) const
{

    callback_fn(SDL_GetKeyName(key), press_type, *target_comp);
}