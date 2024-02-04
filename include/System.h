/* 
dsv-cprog-space-invaders - A space invaders inspired shooter written in C++ with SDL2
Copyright (C) 2024 Edwin Sundberg and Erik Lind Gou-Said

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
