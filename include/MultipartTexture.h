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
    SDL_Texture *get_texture() const { return texture; }
    virtual ~MultipartTexture() { SDL_DestroyTexture(texture); }

    // Forbid value semantics
    MultipartTexture(const MultipartTexture&) = delete;
    MultipartTexture& operator=(const MultipartTexture&) = delete;
    MultipartTexture(MultipartTexture&&) = delete;
    MultipartTexture& operator=(MultipartTexture&&) = delete;
protected:
    MultipartTexture(std::shared_ptr<Session> session, SDL_Texture *tex) : session(session), texture(tex) {}
    std::shared_ptr<Session> session;
private:
    SDL_Texture *texture;
};

#endif