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
#ifndef MULTIPARTRECTANGLETEXTURE_H
#define MULTIPARTRECTANGLETEXTURE_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <memory>
#include <Color.h>
#include <Session.h>

// Spelmotorklass - En rektangulär textur med en viss färg för MultipartComponent
class MultipartRectangleTexture : public MultipartTexture
{
public:
    static std::shared_ptr<MultipartRectangleTexture> create_instance(std::shared_ptr<Session> session, int width, int height, Color color);
private:
    MultipartRectangleTexture(std::shared_ptr<Session> session, int width, int height, Color color);
};



#endif