#include <string>
#include <iostream>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

int main(int argc, char* argv[] ) {

   if (SDL_Init(SDL_INIT_VIDEO) < 0){
      std::cout << "Error Initializing SDL Video: " << SDL_GetError();
   }

   std::cout << "SDL Video Initialized!" << std::endl;

   SDL_Window *window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
      
        std::cout << "Error " << SDL_GetError();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,  -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){ 
        std::cout << "Error " << SDL_GetError();
        return 1;
    }

   std::cout << "End Program using the application\'s windows menu \"quit\" or just close the window!" << std::endl;

   bool running = true;
   while (running){
      SDL_Event event;
      while(SDL_PollEvent(&event)){
         switch(event.type){
            case SDL_QUIT:
               running = false;
               break;

            default:
               break;

         }
      }

      SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
      SDL_RenderClear(renderer);

      SDL_RenderPresent(renderer);



   }



   std::string greetings = "Hello";
   std::cout << greetings << std::endl;

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;   
}