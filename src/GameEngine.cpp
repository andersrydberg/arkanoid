//
// Created by Anders Rydberg on 2022-11-15.
//

#include "GameEngine.h"
#include "World.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


GameEngine& GameEngine::getInstance(const std::string& title, int windowW, int windowH) {
    static GameEngine engine(title, windowW, windowH);
    return engine;
}

GameEngine::GameEngine(const std::string& title, int windowW, int windowH) :
title(title), windowW(windowW), windowH(windowH), window(nullptr), rend(nullptr), world(nullptr) {
    bInitialized = init();
}

GameEngine::~GameEngine() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete world;
}

bool GameEngine::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

#if __APPLE__
// necessary on my Mac
// the default "metal" renderer is extremely laggy for some reason
// https://stackoverflow.com/questions/59700423/why-is-sdl-so-much-slower-on-mac-than-linux
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
#endif

    window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,windowW,windowH,0);
    if (!window)
        return false;

    rend = SDL_CreateRenderer(window,-1,0);
    if (!rend)
        return false;

    world = new World(*this);
    return true;
}

void GameEngine::run() {
    if (!bInitialized)
        ;// throw error

    int millisecondsPerTick = 1000 / fps;
    while (!bQuit) {

        Uint32 nextTick = SDL_GetTicks() + millisecondsPerTick;
        // poll events; if any - dispatch them to components to be handled
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    world->mousePressed(&event);
                    break;
                case SDL_MOUSEBUTTONUP:
                    world->mouseReleased(&event);
                    break;
                case SDL_MOUSEMOTION:
                    world->mouseMoved(&event);
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_UP:
                            world->upKeyPressed(&event);
                            break;
                        case SDLK_DOWN:
                            world->downKeyPressed(&event);
                            break;
                        case SDLK_LEFT:
                            world->leftKeyPressed(&event);
                            break;
                        case SDLK_RIGHT:
                            world->rightKeyPressed(&event);
                            break;
                        default:
                            auto iter = functionMap.find(SDL_GetKeyName(event.key.keysym.sym));
                            if (iter != functionMap.end())
                                iter->second(&event);
                    }
                    break;
                case SDL_QUIT:
                    quit();
                    break;
            }
        }

        // tick all components
        world->tick();
        world->checkCollisions();


        // draw window
        SDL_RenderClear(rend);
        world->draw();
        SDL_RenderPresent(rend);

        // sleep the necessary amount of time left until next tick
        int diff = nextTick - SDL_GetTicks();
        if (diff > 0)
            SDL_Delay(diff);

    }
}

bool GameEngine::initWithErrors() const {
    return !bInitialized;
}

void GameEngine::setTitle(const std::string &newTitle) {
    title = newTitle;
    SDL_SetWindowTitle(window, newTitle.c_str());
}

void GameEngine::quit() {
    bQuit = true;
}



SDL_Texture* GameEngine::getTextureFromImage(const std::string& filepath) {
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    return texture;
}
