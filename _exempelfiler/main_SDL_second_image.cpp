//
//  sdl2_second
//  

#include <iostream>
#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.

// Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// Bifogas endast för test av SDL installation! 

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>

/*  PATH TO YOUR RESOURCE FOLDER 'resources'
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*
*   Change to your own path if you choose a different approach!
*   Absolut Path(Second choice)
*   gResPath = "/Users/kjellna/dev/cpp/sdl2_second/resources/";
*
*   If you need to copy your 'resources' folder into directory
*   '/build/debug/', in that case change gResPath="./resources/"
*/

//#define FPS 60


int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return EXIT_FAILURE;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "Error SDL_ttf Initialization : " << SDL_GetError();
		return EXIT_FAILURE;
	}
	
	SDL_Window* window 		= SDL_CreateWindow("Window", 100, 100, 800, 600, 0);
	SDL_Renderer* renderer 	= SDL_CreateRenderer(window, -1, 0);

	SDL_Surface* bg_sur = IMG_Load( (constants::gResPath + "images/bg.jpg").c_str() );

	SDL_Texture* bg_tex = SDL_CreateTextureFromSurface(renderer, bg_sur);
	SDL_FreeSurface(bg_sur);

	 std::cout << "End Program using the application\'s windows menu \"quit\" or just close the window!" << std::endl;

	// Loop till dess att programmet avslutas!
	bool running = true;
	while (running) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	// Städa innan programmet avslutas!

	SDL_DestroyTexture(bg_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	
	return EXIT_SUCCESS;
}