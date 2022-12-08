//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <string>

class System {

public:
    System();
    ~System();
    bool initWithErrors() const;

    int getWindowWidth() const;
    int getWindowHeight() const;

    void setWindowSize(int w, int h) const;
    void setWindowTitle(const std::string& title) const;

    SDL_Window* window;
    SDL_Renderer* rend;


private:
    int init();

    int initStatus;
};

// declaration of global variable
// needs to be defined (once) in cpp-files
extern System sys;

#endif
