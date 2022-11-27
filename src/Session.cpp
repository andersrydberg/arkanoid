//
// Created by Anders Rydberg on 2022-11-21.
//

#include <SDL2/SDL.h>
#include "System.h"
#include "Session.h"

#define FPS 60

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
                    for (Component* comp : comps)
                        comp->mouseDown(&event);
                    break;
                case SDL_QUIT:
                    quit = true; break;
            }
        }

        // tick all components
        for (Component* comp : comps)
            comp->tick();

        // add any new components
        for (Component* comp : addQueue)
            comps.push_back(comp);
        addQueue.clear();

        // remove any "dead" components, free memory
        for (Component* comp : removeQueue) {
            for (std::vector<Component*>::iterator iter = comps.begin();
            iter != comps.end(); iter++) {
                if (*iter == comp) {
                    comps.erase(iter);
                    delete comp;
                    break; // inner for (continue with the next comp)
                }
            }
        }
        removeQueue.clear();

        // draw window
        SDL_RenderClear(sys.rend);
        for (Component* comp : comps) {
            comp->draw();
        }
        SDL_RenderPresent(sys.rend);

        // sleep the necessary amount of time left until next tick
        int diff = nextTick - SDL_GetTicks();
        if (diff > 0)
            SDL_Delay(diff);

    }

}


void Session::add(Component *comp) {
    addQueue.push_back(comp);
}

void Session::remove(Component *comp) {
    removeQueue.push_back(comp);
}