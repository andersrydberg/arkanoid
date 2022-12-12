//
// Created by Anders Rydberg on 2022-11-21.
//

#include <SDL2/SDL.h>
#include "System.h"
#include "Session.h"
#include <iostream>

Session::Session() {
    world = new World();
}

Session::~Session() {
    delete world;
}

void Session::run() {

    int millisecondsPerTick = 1000 / fps;
    while (!bQuit) {

        Uint32 nextTick = SDL_GetTicks() + millisecondsPerTick;
        // poll events; if any - dispatch them to components to be handled
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    world->mouseDown(&event); break;
                case SDL_QUIT:
                    bQuit = true; break;
            }
        }

        // tick all components
        world->tick();


        // draw window
        SDL_RenderClear(sys.rend);
        world->draw();
        SDL_RenderPresent(sys.rend);

        // sleep the necessary amount of time left until next tick
        int diff = nextTick - SDL_GetTicks();
        if (diff > 0)
            SDL_Delay(diff);

    }

}

Session ses;