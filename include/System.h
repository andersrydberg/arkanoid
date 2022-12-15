//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <string>

class System {

public:
    ~System();
    static System& getInstance(const std::string& title, int windowW, int windowH);


    bool initWithErrors() const;

    int getWindowWidth() const;
    int getWindowHeight() const;

    void setWindowTitle(const std::string& title) const;

    SDL_Window* window;
    SDL_Renderer* rend;


private:
    System(const std::string& title, int windowW, int windowH);

    int init(const std::string& title, int windowW, int windowH);

    bool bInitWithErrors;
};

#endif
