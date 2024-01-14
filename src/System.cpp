#include <System.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


System::System() {
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Game", 10, 10, 850, 850, 0);
    ren = SDL_CreateRenderer(win, -1, 0);
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
    sound_bank = std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>>();
    TTF_Init();
}

System::~System() {
    Mix_CloseAudio();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

void System::play_sound(std::string path, int loops) {
    if(this->sound_bank.count(path) == 0)
    {
        this->sound_bank.insert(std::make_pair(path, std::unique_ptr<Mix_Chunk>(Mix_LoadWAV((constants::gResPath + path).c_str()))));
    }
    Mix_PlayChannel(-1, this->sound_bank.at(path).get(), loops);
}

SDL_Window* System::get_window() {
    return win;
}

SDL_Renderer* System::get_renderer() {
    return ren;
}

System sys;