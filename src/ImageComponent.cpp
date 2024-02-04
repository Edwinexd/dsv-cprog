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
#include<ImageComponent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

ImageComponent::ImageComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string path, bool has_collision) : Component(session, x, y, w, h, has_collision) {
    SDL_Surface* surf = IMG_Load((constants::gResPath + path).c_str());
    tex = SDL_CreateTextureFromSurface(sys.get_renderer(), surf);
    SDL_FreeSurface(surf);
}

std::shared_ptr<ImageComponent> ImageComponent::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string path, bool has_collision) {
    return std::shared_ptr<ImageComponent>(new ImageComponent(session, x, y, w, h, path, has_collision));
}

void ImageComponent::render() const {
    const SDL_Rect &rect = get_rect();
    SDL_RenderCopy(sys.get_renderer(), tex, NULL, &rect);
}

ImageComponent::~ImageComponent() {
    SDL_DestroyTexture(tex);
}
