#ifndef MULTIPARTCOMPONENT_H
#define MULTIPARTCOMPONENT_H
#include<Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>

class MultipartComponent : public Component
{
public:
    static std::shared_ptr<MultipartComponent> createInstance(int x, int y, int w, int h, bool has_collission) {
        return std::shared_ptr<MultipartComponent>(new MultipartComponent(x, y, w, h, has_collission));
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
    MultipartComponent(int x, int y, int w, int h, bool has_collission) : Component(x, y, w, h, has_collission) {
        current_texture = 0;
        textures = std::vector<std::shared_ptr<MultipartTexture>>();
    }
private:
    std::vector<std::shared_ptr<MultipartTexture>> textures;
    std::size_t current_texture;
};

#endif