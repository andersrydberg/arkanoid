//
// Created by Anders Rydberg on 2022-11-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "System.h"
#include "Session.h"


void Session::run() {

    bool quit = false;
    while (!quit) {

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

        // remove any "dead" components
        for (Component* comp : removeQueue) {
            for (std::vector<Component*>::iterator iter = comps.begin();
            iter != comps.end(); iter++) {
                if (*iter == comp) {
                    comps.erase(iter);
                    break; // inner for (continue with the next comp)
                }
            }
        }
        removeQueue.clear();

        // draw window
        SDL_RenderClear(sys.rend);
        if (backgroundTexture)
            SDL_RenderCopy(sys.rend, backgroundTexture, NULL, NULL);
        for (Component* comp : comps) {
            comp->draw();
        }
        SDL_RenderPresent(sys.rend);

    }

}


void Session::add(Component *comp) {
    addQueue.push_back(comp);
}

void Session::remove(Component *comp) {
    removeQueue.push_back(comp);
}

void Session::setBackground(const std::string &filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    backgroundTexture = SDL_CreateTextureFromSurface(sys.rend, surface);
    SDL_FreeSurface(surface);
}
