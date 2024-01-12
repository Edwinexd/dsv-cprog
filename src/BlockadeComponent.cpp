#include <BlockadeComponent.h>
#include <MultipartImageTexture.h>
#include <ImageComponent.h>

BlockadeComponent::BlockadeComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path) : Enemy(session, x, y, w, h, true, {0,0}, hp, alive_image_path, dead_image_path) {
    health_text = TextComponent::create_instance(session, x, y-h/2, w, h/2, std::to_string(hp), { 255, 255, 255, 255}, Font::REGULAR);
    session->add_component(health_text);
    // TODO, move health % levels to Enemy class
    auto medium_health = MultipartImageTexture::create_instance(session, "images/castle_medium_health.png");
    auto low_health = MultipartImageTexture::create_instance(session, "images/castle_low_health.png");
    add_texture(medium_health);
    add_texture(low_health);
}

std::shared_ptr<BlockadeComponent> BlockadeComponent::create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path) {
    return std::shared_ptr<BlockadeComponent>(new BlockadeComponent(session, x, y, w, h, hp, alive_image_path, dead_image_path));
}

void BlockadeComponent::tick() {
    Enemy::tick();
    std::size_t hp = get_hp();
    health_text->set_text(std::to_string(hp));
    if (is_dead()) {
        return;
    }
    if (hp > 7) {
        set_texture(0);
    } else if (hp > 3) {
        set_texture(2);
    } else {
        set_texture(3);
    }
}

void BlockadeComponent::kill() {
    Enemy::kill();
    session->play_sound("sounds/big_explosion.wav", 0);
}

BlockadeComponent::~BlockadeComponent() {
    session->remove_component(health_text);
    session->remove_component(image_component);
}