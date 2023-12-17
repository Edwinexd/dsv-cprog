//
//  sdl2_first
//  

#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  // Initialisera SDL, så att det kan användas!
  SDL_Init(SDL_INIT_EVERYTHING);
  std::cout << "SDL är nu initialiserad och redo för användning!" << std::endl;

  // Här ska naturligtvis någonting hända, men inte denna gång.
  
  // Nu avslutas programmet.

  // Rensa upp SDL innan programmet avslutas!
  SDL_Quit();
  std::cout << "SDL är nu upprensat innan programavslut!" << std::endl;
  
  return 0;
}
