//
// Created by Anders Rydberg on 2022-11-15.
//

#include "System.h"
#include <SDL2/SDL.h>

System::System() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
            "Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            600, 400, 0);
    rend = SDL_CreateRenderer(window,-1, 0);
}

System::~System() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

System sys;
