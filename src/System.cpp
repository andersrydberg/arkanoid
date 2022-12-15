//
// Created by Anders Rydberg on 2022-11-15.
//

#include "System.h"
#include <SDL2/SDL.h>

System::System(const std::string& title, int windowW, int windowH) {
    bInitWithErrors = init(title, windowW, windowH);
}

System& System::getInstance(const std::string& title, int windowW, int windowH) {
    static System sys(title, windowW, windowH);
    return sys;
}

System::~System() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool System::initWithErrors() const {
    return bInitWithErrors;
}


int System::init(const std::string& title, int windowW, int windowH) {
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


void System::setWindowTitle(const std::string &title) const {
    SDL_SetWindowTitle(window, title.c_str());
}
