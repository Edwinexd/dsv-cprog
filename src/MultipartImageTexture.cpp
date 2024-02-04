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
#include <MultipartImageTexture.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <Session.h>
#include <Constants.h>

MultipartImageTexture::MultipartImageTexture(std::shared_ptr<Session> session, std::string path) : MultipartTexture(session, [path]() {
    SDL_Surface* surf = IMG_Load((constants::gResPath + path).c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(sys.get_renderer(), surf);
    SDL_FreeSurface(surf);
    return tex;
}()) {}

std::shared_ptr<MultipartImageTexture> MultipartImageTexture::create_instance(std::shared_ptr<Session> session, std::string path) {
    return std::shared_ptr<MultipartImageTexture>(new MultipartImageTexture(session, path));
}