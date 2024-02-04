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
#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H
#include <Session.h>
#include <Component.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include <Color.h>
#include <Fonts.h>

// Spelmotorklass - Enkel text, härleds från Component
class TextComponent : public Component
{
public:
    // Create a new instance of TextComponent and return it as a unique_ptr, add to session via session.add_component(text_component)
    // Note: Color alpha is ignored
    static std::shared_ptr<TextComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int max_width, int max_height, std::string text, Color color, Font f);
    void render() const override;
    void tick() {};
    ~TextComponent();
    std::string get_text() const { return text; }
    void set_text(std::string text);
protected:
    TextComponent(std::shared_ptr<Session> session, int x, int y, int max_width, int max_height, std::string text, Color color, Font f);
private:
    int max_width;
    int max_height;
    std::string text;
    SDL_Texture *tex;
    TTF_Font* font;
    Color color;
    int calculate_width(std::string text);
    void draw_text(std::string text);

};

#endif
