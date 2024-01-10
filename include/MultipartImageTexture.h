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
    static std::shared_ptr<MultipartImageTexture> create_instance(std::shared_ptr<Session> session, std::string path) {
        return std::shared_ptr<MultipartImageTexture>(new MultipartImageTexture(session, path));
    }
protected:
    MultipartImageTexture(std::shared_ptr<Session> session, std::string path);
};




#endif