#include <Component.h>
#include <MultipartComponent.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include <System.h>
#include <stdexcept>

void MultipartComponent::render() const {
    if (textures.size() == 0) {
        throw std::runtime_error("No textures in MultipartComponent");
    }
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, textures[current_texture]->getTexture(), NULL, &rect);
}

void MultipartComponent::addTexture(std::shared_ptr<MultipartTexture> tex) {
    textures.push_back(tex);
}

void MultipartComponent::removeTexture(int index) {
    textures.erase(textures.begin() + index);
}

void MultipartComponent::removeTexture(std::shared_ptr<MultipartTexture> tex) {
    for (std::size_t i = 0; i < textures.size(); i++) {
        if (textures[i] == tex) {
            removeTexture(i);
            break;
        }
    }
}

void MultipartComponent::nextTexture() {
    setTexture(++current_texture % textures.size());
}

void MultipartComponent::setTexture(std::size_t index) {
    if (index >= textures.size()) {
        throw std::runtime_error("Index out of bounds in MultipartComponent::setTexture");
    }
    current_texture = index;
}

MultipartComponent::~MultipartComponent() {
    textures.clear();
}