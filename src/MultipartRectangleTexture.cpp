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
#include <MultipartRectangleTexture.h>
#include <Color.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <Session.h>
#include <Constants.h>

MultipartRectangleTexture::MultipartRectangleTexture(std::shared_ptr<Session> session, int w, int h, Color color) : MultipartTexture(session, [w, h, color]() {
    SDL_Renderer* ren = sys.get_renderer();
    SDL_Texture* tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(ren, tex);
    SDL_SetRenderDrawColor(ren, color.get_r(), color.get_g(), color.get_b(), color.get_a());
    SDL_RenderClear(ren);
    SDL_SetRenderTarget(ren, NULL);
    return tex;
}()) {}

std::shared_ptr<MultipartRectangleTexture> MultipartRectangleTexture::create_instance(std::shared_ptr<Session> session, int w, int h, Color color) {
    return std::shared_ptr<MultipartRectangleTexture>(new MultipartRectangleTexture(session, w, h, color));
}
