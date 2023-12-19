#include<ImageComponent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <system.h>

ImageComponent::ImageComponent(int x, int y, int w, int h, std::string path, bool has_collission) : Component(x, y, w, h, has_collission) {
    SDL_Surface* surf = IMG_Load((constants::gResPath + path).c_str());
    tex = SDL_CreateTextureFromSurface(sys.ren, surf);
    SDL_FreeSurface(surf);
}

void ImageComponent::render() const {
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, tex, NULL, &rect);
}

ImageComponent::~ImageComponent() {
    SDL_DestroyTexture(tex);
}
