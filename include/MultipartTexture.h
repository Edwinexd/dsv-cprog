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
#ifndef MULTIPARTTEXTURE_H
#define MULTIPARTTEXTURE_H
#include <Component.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

// Spelmotorklass - Abstraktion för en SDL_Texture som kan användas i MultipartComponent
class MultipartTexture
{
public:
    SDL_Texture *get_texture() const { return texture; }
    virtual ~MultipartTexture() { SDL_DestroyTexture(texture); }

    // Forbid value semantics
    MultipartTexture(const MultipartTexture&) = delete;
    MultipartTexture& operator=(const MultipartTexture&) = delete;
    MultipartTexture(MultipartTexture&&) = delete;
    MultipartTexture& operator=(MultipartTexture&&) = delete;
protected:
    MultipartTexture(std::shared_ptr<Session> session, SDL_Texture *tex) : session(session), texture(tex) {}
    std::shared_ptr<Session> session;
private:
    SDL_Texture *texture;
};

#endif