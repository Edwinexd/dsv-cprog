#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H
#include<Component.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>

class ImageComponent : public Component
{
public:
    static std::shared_ptr<ImageComponent> createInstance(int x, int y, int w, int h, std::string path, bool has_collission) {
        return std::shared_ptr<ImageComponent>(new ImageComponent(x, y, w, h, path, has_collission));
    }
    void render() const override;
    void tick() {};
    ~ImageComponent();
protected:
    ImageComponent(int x, int y, int w, int h, std::string path, bool has_collission);
private:
    SDL_Texture* tex;
};


#endif
