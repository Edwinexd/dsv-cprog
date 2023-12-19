#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

System::System() {
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Game", 10, 10, 850, 850, 0);
    ren = SDL_CreateRenderer(win, -1, 0);
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
    sounds = std::vector<Mix_Chunk*>();
    TTF_Init();
}

System::~System() {
    for (Mix_Chunk* sound : sounds) {
        Mix_FreeChunk(sound);
        delete sound;
    }
    Mix_CloseAudio();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

System sys;