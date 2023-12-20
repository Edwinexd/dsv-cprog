#ifndef MULTIPARTCOMPONENT_H
#define MULTIPARTCOMPONENT_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>

class MultipartComponent : public Component
{
public:
    static std::unique_ptr<MultipartComponent> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision) {
        return std::unique_ptr<MultipartComponent>(new MultipartComponent(session, x, y, w, h, has_collision));
    }
    void render() const override;
    void tick() {};
    void addTexture(std::shared_ptr<MultipartTexture> tex);
    void removeTexture(int index);
    void removeTexture(std::shared_ptr<MultipartTexture> tex);
    void setTexture(size_t index);
    void nextTexture();
    ~MultipartComponent();
protected:
    MultipartComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision) : Component(session, x, y, w, h, has_collision) {
        current_texture = 0;
        textures = std::vector<std::shared_ptr<MultipartTexture>>();
    }
private:
    std::vector<std::shared_ptr<MultipartTexture>> textures;
    std::size_t current_texture;
};

#endif