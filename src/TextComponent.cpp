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
#include <TextComponent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <Fonts.h>

TextComponent::TextComponent(std::shared_ptr<Session> session, int x, int y, int max_width, int max_height, std::string text, Color c, Font f) : Component(session, x, y, 0, 0, false), color(c) {
    this->max_width = max_width;
    this->max_height = max_height;
    this->color = color;
    font = TTF_OpenFont((constants::gResPath + get_font_path(f)).c_str(), 24);
    draw_text(text);
}

std::shared_ptr<TextComponent> TextComponent::create_instance(std::shared_ptr<Session> session, int x, int y, int max_width, int max_height, std::string text, Color color, Font f) {
    return std::shared_ptr<TextComponent>(new TextComponent(session, x, y, max_width, max_height, text, color, f));
}

void TextComponent::render() const {
    const SDL_Rect &rect = get_rect();
    SDL_RenderCopy(sys.get_renderer(), tex, NULL, &rect);
}

void TextComponent::set_text(std::string text) {
    SDL_DestroyTexture(tex);
    draw_text(text);
}

// Sets the text and resizes the component to fit the text
// NOTE: Caller is responsible for deleting any old texture (tex) before calling this function
void TextComponent::draw_text(std::string text) {
    this->text = text;
    
    SDL_Color sdl_color = { color.get_r(), color.get_g(), color.get_b() };
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), sdl_color);
    tex = SDL_CreateTextureFromSurface(sys.get_renderer(), surf);
    SDL_FreeSurface(surf);
    
    int w = calculate_width(text);
    set_width(w);
    set_height(max_height);
}

// Returns the optimal width for the text based on the height of the component
int TextComponent::calculate_width(std::string text) {
    int w, h;
    TTF_SizeUTF8(font, text.c_str(), &w, &h);
    return w * max_height / h;
}

TextComponent::~TextComponent() {
    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);
}