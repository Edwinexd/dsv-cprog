#ifndef MULTIPARTTEXTURE_H
#define MULTIPARTTEXTURE_H
#include <Component.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

class MultipartTexture
{
public:
    SDL_Texture *getTexture() const { return texture; }
    virtual ~MultipartTexture() { SDL_DestroyTexture(texture); }
protected:
    MultipartTexture(SDL_Texture *tex) : texture(tex) {}
private:
    SDL_Texture *texture;
};

#endif