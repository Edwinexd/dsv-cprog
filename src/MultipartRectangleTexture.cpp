#include <MultipartRectangleTexture.h>
#include <Color.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <Session.h>
#include <Constants.h>

MultipartRectangleTexture::MultipartRectangleTexture(std::shared_ptr<Session> session, int w, int h, Color color) : MultipartTexture(session, [w, h, color]() {
    SDL_Renderer* ren = sys.get_renderer();
    SDL_Texture* tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(ren, tex);
    SDL_SetRenderDrawColor(ren, color.get_r(), color.get_g(), color.get_b(), color.get_a());
    SDL_RenderClear(ren);
    SDL_SetRenderTarget(ren, NULL);
    return tex;
}()) {}

std::shared_ptr<MultipartRectangleTexture> MultipartRectangleTexture::create_instance(std::shared_ptr<Session> session, int w, int h, Color color) {
    return std::shared_ptr<MultipartRectangleTexture>(new MultipartRectangleTexture(session, w, h, color));
}
