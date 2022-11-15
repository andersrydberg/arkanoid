//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef PROGC_PROJEKT_SYSTEM_H
#define PROGC_PROJEKT_SYSTEM_H

#include <SDL2/SDL.h>

class System {
public:
    System();
    ~System();
private:
    SDL_Window* window;
    SDL_Renderer* rend;
};

extern System sys;

#endif //PROGC_PROJEKT_SYSTEM_H
