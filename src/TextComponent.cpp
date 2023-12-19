#include <TextComponent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

TextComponent::TextComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string text) : Component(session, x, y, w, h, false) {
    this->text = text;
    font = TTF_OpenFont((constants::gResPath + "fonts/Roboto-Thin.ttf").c_str(), 24);
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
    tex = SDL_CreateTextureFromSurface(sys.ren, surf);
    SDL_FreeSurface(surf);
}

void TextComponent::render() const {
    const SDL_Rect &rect = get_rect();
    SDL_RenderCopy(sys.ren, tex, NULL, &rect);
}

void TextComponent::setText(std::string text) {
    SDL_DestroyTexture(tex);
    this->text = text;
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
    tex = SDL_CreateTextureFromSurface(sys.ren, surf);
    SDL_FreeSurface(surf);
}

TextComponent::~TextComponent() {
    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);
}