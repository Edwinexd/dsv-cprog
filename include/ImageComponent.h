#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H
#include <Session.h>
#include <Component.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>

class ImageComponent : public Component
{
public:
    static std::unique_ptr<ImageComponent> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string path, bool has_collision) {
        return std::unique_ptr<ImageComponent>(new ImageComponent(session, x, y, w, h, path, has_collision));
    }
    void render() const override;
    void tick() {};
    ~ImageComponent();
protected:
    ImageComponent(std::shared_ptr<Session> session, int x, int y, int w, int h, std::string path, bool has_collision);
private:
    SDL_Texture* tex;
};


#endif