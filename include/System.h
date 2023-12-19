#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Constants.h"
#include <unordered_map>
#include <memory>


struct System
{
	System();
	~System();
	void play_sound(std::string path, int loops);

	SDL_Window* win;
	SDL_Renderer* ren;
	// vector for storing all the sounds
    std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>> sound_bank;
};

extern System sys;

#endif
