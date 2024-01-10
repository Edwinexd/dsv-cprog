#include <BlockadeComponent.h>
#include <MultipartImageTexture.h>
#include <ImageComponent.h>

BlockadeComponent::BlockadeComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, int hp, std::string alive_image_path, std::string dead_image_path) : Enemy(session, x, y, w, h, true, hp, alive_image_path, dead_image_path) {
    auto text_component = TextComponent::create_instance(session, x, y-h/2, w, h/2, std::to_string(hp), { 255, 255, 255, 255}, Font::REGULAR);
    health_text = std::dynamic_pointer_cast<TextComponent>(session->add_component(std::move(text_component)));
    // TODO, move health % levels to Enemy class
    auto medium_health = MultipartImageTexture::create_instance(session, "images/castle_medium_health.png");
    auto low_health = MultipartImageTexture::create_instance(session, "images/castle_low_health.png");
    add_texture(medium_health);
    add_texture(low_health);
}

void BlockadeComponent::tick() {
    handle_death_tick();
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

BlockadeComponent::~BlockadeComponent() {
    session->remove_component(health_text);
    session->remove_component(image_component);
}