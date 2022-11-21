//
// Created by Anders Rydberg on 2022-11-15.
//

#include "System.h"
#include <SDL2/SDL.h>

System::System() {
    initStatus = init();
}

System::~System() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool System::initWithErrors() const {
    return initStatus;
}

int System::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return 1;

    window = SDL_CreateWindow("Game",SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,600,400,0);
    if (!window)
        return 1;

    rend = SDL_CreateRenderer(window,-1,0);
    if (!rend)
        return 1;

    return 0;
}

System sys;
