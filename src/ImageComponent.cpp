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
