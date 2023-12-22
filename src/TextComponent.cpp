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

void TextComponent::render() const {
    const SDL_Rect &rect = get_rect();
    SDL_RenderCopy(sys.ren, tex, NULL, &rect);
}

void TextComponent::setText(std::string text) {
    SDL_DestroyTexture(tex);
    draw_text(text);
}

// Sets the text and resizes the component to fit the text
// NOTE: Caller is responsible for deleting any old texture (tex) before calling this function
void TextComponent::draw_text(std::string text) {
    this->text = text;
    
    SDL_Color sdl_color = { color.r, color.g, color.b };
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), sdl_color);
    tex = SDL_CreateTextureFromSurface(sys.ren, surf);
    SDL_FreeSurface(surf);
    
    rect.w = calculate_width(text);
    rect.h = max_height;
    if (rect.w > max_width) {
        rect.w = max_width;
        rect.h = surf->h * max_width / surf->w;
    }
}

// Returns the optimal width for the text based on the height of the component
int TextComponent::calculate_width(std::string text) {
    int w, h;
    TTF_SizeUTF8(font, text.c_str(), &w, &h);
    return w * get_rect().h / h;
}

TextComponent::~TextComponent() {
    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);
}