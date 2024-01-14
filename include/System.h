#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>
#include <Constants.h>
#include <unordered_map>
#include <memory>

// Spelmotorklass - Systemklass som hanterar huvuddelar av SDL
struct System
{
	public:
	System();
	~System();
	void play_sound(std::string path, int loops);

	SDL_Window* get_window();
	SDL_Renderer* get_renderer();



	private:
	SDL_Window* win;
	SDL_Renderer* ren;
    std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>> sound_bank;
};

extern System sys;

#endif
