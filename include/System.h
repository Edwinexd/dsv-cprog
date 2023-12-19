#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Constants.h"

/*
struct System
{
	System();
	~System();
	void play_sound(std::string path, int loops = -1) {
		Mix_Chunk* sound = Mix_LoadWAV( (constants::gResPath + path).c_str() );
		Mix_PlayChannel(-1, sound, loops);
		sounds.push_back(sound);
	}

	SDL_Window* win;
	SDL_Renderer* ren;
	// vector for storing all the sounds
	std::vector<Mix_Chunk*> sounds;
};
*/
extern System sys;

#endif
