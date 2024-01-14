#include <Component.h>
#include <MultipartComponent.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

MultipartComponent::MultipartComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d) : Component(session, x, y, w, h, has_collision, d) {
    current_texture = 0;
    textures = std::vector<std::shared_ptr<MultipartTexture>>();
}

std::shared_ptr<MultipartComponent> MultipartComponent::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d) {
    return std::shared_ptr<MultipartComponent>(new MultipartComponent(session, x, y, w, h, has_collision, d));
}

void MultipartComponent::render() const {
    if (textures.size() == 0) {
        throw std::runtime_error("No textures in MultipartComponent");
    }
    const SDL_Rect& rect = get_rect();
    SDL_RenderCopy(sys.ren, textures[current_texture]->get_texture(), NULL, &rect);
}

void MultipartComponent::add_texture(std::shared_ptr<MultipartTexture> tex) {
    textures.push_back(tex);
}

void MultipartComponent::remove_texture(int index) {
    textures.erase(textures.begin() + index);
}

void MultipartComponent::remove_texture(std::shared_ptr<MultipartTexture> tex) {
    for (std::size_t i = 0; i < textures.size(); i++) {
        if (textures[i] == tex) {
            remove_texture(i);
            break;
        }
    }
}

void MultipartComponent::next_texture() {
    set_texture(++current_texture % textures.size());
}

void MultipartComponent::set_texture(std::size_t index) {
    if (index < 0 || index >= textures.size()) {
        throw std::runtime_error("Index out of bounds in MultipartComponent::set_texture");
    }
    current_texture = index;
}

MultipartComponent::~MultipartComponent() {
    textures.clear();
}