//
// Created by Anders Rydberg on 2022-11-21.
//

#include <SDL2/SDL.h>
#include "System.h"
#include "Session.h"
#include <iostream>

#define FPS 60

Session::Session() {
    map = new Map();
}

Session::~Session() {
    delete map;
}

void Session::run() {

    bool quit = false;
    int millisecs_per_tick = 1000 / FPS;
    while (!quit) {

        Uint32 nextTick = SDL_GetTicks() + millisecs_per_tick;
        // poll events; if any - dispatch them to components to be handled
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    map->mouseDown(&event); break;
                case SDL_QUIT:
                    quit = true; break;
            }
        }

        // tick all components
        map->tick();


        // draw window
        SDL_RenderClear(sys.rend);
        map->draw();
        SDL_RenderPresent(sys.rend);

        // sleep the necessary amount of time left until next tick
        int diff = nextTick - SDL_GetTicks();
        //std::cout << diff << std::endl;
        if (diff > 0)
            SDL_Delay(diff);

    }

}

Session ses;