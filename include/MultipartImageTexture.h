#ifndef MULTIPARTIMAGETEXTURE_H
#define MULTIPARTIMAGETEXTURE_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>

class MultipartImageTexture : public MultipartTexture
{
public:
    static std::shared_ptr<MultipartImageTexture> createInstance(std::string path) {
        return std::shared_ptr<MultipartImageTexture>(new MultipartImageTexture(path));
    }
protected:
    MultipartImageTexture(std::string path);
};



#endif