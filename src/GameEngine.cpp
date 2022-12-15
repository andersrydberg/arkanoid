//
// Created by Anders Rydberg on 2022-11-15.
//

#include "GameEngine.h"
#include <SDL2/SDL.h>

GameEngine::GameEngine(const std::string& title, int windowW, int windowH) {
    bInitWithErrors = init(title, windowW, windowH);
}

void GameEngine::initialize(const std::string& title, int windowW, int windowH) {
    bInitWithErrors = init(title, windowW, windowH);
}

GameEngine& GameEngine::getInstance(const std::string& title, int windowW, int windowH) {
    static GameEngine sys(title, windowW, windowH);
    return sys;
}


GameEngine::~GameEngine() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete world;
}


bool GameEngine::initWithErrors() const {
    return bInitWithErrors;
}


int GameEngine::init(const std::string& title, int windowW, int windowH) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return true;

#if __APPLE__
    // necessary on my Mac
    // the default "metal" renderer is extremely laggy for some reason
    // https://stackoverflow.com/questions/59700423/why-is-sdl-so-much-slower-on-mac-than-linux
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
#endif

    window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,windowW,windowH,0);
    if (!window)
        return true;

    rend = SDL_CreateRenderer(window,-1,0);
    if (!rend)
        return true;

    return false;
}

int GameEngine::getWindowWidth() const {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return w;
}

int GameEngine::getWindowHeight() const {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return h;
}




void GameEngine::setTitle(const std::string &title) const {
    SDL_SetWindowTitle(window, title.c_str());
}

void GameEngine::run() {

    int millisecondsPerTick = 1000 / fps;
    while (!bQuit) {

        Uint32 nextTick = SDL_GetTicks() + millisecondsPerTick;
        // poll events; if any - dispatch them to components to be handled
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    world->mouseDown(sys, &event);
                    break;
                case SDL_QUIT:
                    quit();
                    break;
            }
        }

        // tick all components
        world->tick(sys);


        // draw window
        SDL_RenderClear(sys.rend);
        world->draw(sys);
        SDL_RenderPresent(sys.rend);

        // sleep the necessary amount of time left until next tick
        int diff = nextTick - SDL_GetTicks();
        if (diff > 0)
            SDL_Delay(diff);

    }
}
