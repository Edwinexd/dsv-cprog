#include <MultipartRectangleTexture.h>
#include <Color.h>
#include <SDL2/SDL.h>
#include <string>
#include <Session.h>
#include <Constants.h>

MultipartRectangleTexture::MultipartRectangleTexture(std::shared_ptr<Session> session, int w, int h, Color color) : MultipartTexture(session, [w, h, color]() {
    SDL_Texture* tex = SDL_CreateTexture(sys.ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(sys.ren, tex);
    SDL_SetRenderDrawColor(sys.ren, color.r, color.g, color.b, color.a);
    SDL_RenderClear(sys.ren);
    SDL_SetRenderTarget(sys.ren, NULL);
    return tex;
}()) {}
