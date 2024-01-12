#include <MultipartRectangleTexture.h>
#include <Color.h>
#include <SDL2/SDL.h>
#include <string>
#include <Session.h>
#include <Constants.h>

MultipartRectangleTexture::MultipartRectangleTexture(std::shared_ptr<Session> session, int w, int h, Color color) : MultipartTexture(session, [w, h, color]() {
    SDL_Texture* tex = SDL_CreateTexture(sys.ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(sys.ren, tex);
    SDL_SetRenderDrawColor(sys.ren, color.get_r(), color.get_g(), color.get_b(), color.get_a());
    SDL_RenderClear(sys.ren);
    SDL_SetRenderTarget(sys.ren, NULL);
    return tex;
}()) {}

std::shared_ptr<MultipartRectangleTexture> MultipartRectangleTexture::create_instance(std::shared_ptr<Session> session, int w, int h, Color color) {
    return std::shared_ptr<MultipartRectangleTexture>(new MultipartRectangleTexture(session, w, h, color));
}
