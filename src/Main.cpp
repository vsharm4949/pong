#include <iostream>

#include "SDL2/SDL.h"

int main() {
    std::cout << "Initializing SDL..." << std::endl;
    SDL_Init( SDL_INIT_EVERYTHING );
    std::cout << "Done!" << std::endl;

    std::cout << "Quitting SDL..." << std::endl;
    SDL_Quit();
    std::cout << "Done!" << std::endl;

    return 0;
}

