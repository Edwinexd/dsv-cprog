#ifndef MULTIPARTTEXTURE_H
#define MULTIPARTTEXTURE_H
#include <Component.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

// Spelmotorklass - Abstraktion för en SDL_Texture som kan användas i MultipartComponent
class MultipartTexture
{
public:
    SDL_Texture *get_texture() const { return texture; }
    virtual ~MultipartTexture() { SDL_DestroyTexture(texture); }
protected:
    MultipartTexture(std::shared_ptr<Session> session, SDL_Texture *tex) : session(session), texture(tex) {}
    std::shared_ptr<Session> session;
private:
    SDL_Texture *texture;
};

#endif