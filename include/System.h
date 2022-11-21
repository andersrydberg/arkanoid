//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>

class System {

public:
    System();
    ~System();
    bool initWithErrors() const;

    SDL_Window* window;
    SDL_Renderer* rend;


private:
    int init();

    int initStatus;
};

// declared as 'extern' because?
extern System sys;

#endif
