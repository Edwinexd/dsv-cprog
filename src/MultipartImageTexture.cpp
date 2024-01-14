#include <MultipartImageTexture.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <Session.h>
#include <Constants.h>

MultipartImageTexture::MultipartImageTexture(std::shared_ptr<Session> session, std::string path) : MultipartTexture(session, [path]() {
    SDL_Surface* surf = IMG_Load((constants::gResPath + path).c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(sys.get_renderer(), surf);
    SDL_FreeSurface(surf);
    return tex;
}()) {}

std::shared_ptr<MultipartImageTexture> MultipartImageTexture::create_instance(std::shared_ptr<Session> session, std::string path) {
    return std::shared_ptr<MultipartImageTexture>(new MultipartImageTexture(session, path));
}