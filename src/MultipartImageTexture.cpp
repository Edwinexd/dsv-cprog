#include <MultipartImageTexture.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <System.h>
#include <Constants.h>

MultipartImageTexture::MultipartImageTexture(std::string path) : MultipartTexture([path]() {
    SDL_Surface* surf = IMG_Load((constants::gResPath + path).c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(sys.ren, surf);
    SDL_FreeSurface(surf);
    return tex;
}()) {}
