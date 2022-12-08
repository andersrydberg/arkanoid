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


#if __APPLE__
    // necessary on my Mac
    // the default "metal" renderer is extremely laggy for some reason
    // https://stackoverflow.com/questions/59700423/why-is-sdl-so-much-slower-on-mac-than-linux
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
#endif


    window = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,600,400,0);
    if (!window)
        return 1;

    rend = SDL_CreateRenderer(window,-1,0);
    if (!rend)
        return 1;

    return 0;
}


int System::getWindowWidth() const {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return w;
}

int System::getWindowHeight() const {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return h;
}




void System::setWindowSize(int w, int h) const {
    SDL_SetWindowSize(window, w, h);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void System::setWindowTitle(const std::string &title) const {
    SDL_SetWindowTitle(window, title.c_str());
}


System sys;
