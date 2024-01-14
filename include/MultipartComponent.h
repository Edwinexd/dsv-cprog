#ifndef MULTIPARTCOMPONENT_H
#define MULTIPARTCOMPONENT_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>

// Spelmotorklass - Komponent som kan ha flera olika texturer och byta mellan dem
class MultipartComponent : public Component
{
public:
    static std::shared_ptr<MultipartComponent> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d);
    void render() const override;
    void tick() {
        Component::tick();
    };
    void add_texture(std::shared_ptr<MultipartTexture> tex);
    void remove_texture(size_t index);
    void remove_texture(std::shared_ptr<MultipartTexture> tex);
    void set_texture(size_t index);
    void next_texture();
    std::size_t get_active_texture() const {
        return current_texture;
    }
    ~MultipartComponent();
protected:
    MultipartComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, Direction d);
private:
    std::vector<std::shared_ptr<MultipartTexture>> textures;
    std::size_t current_texture;
};

#endif