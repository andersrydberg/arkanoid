//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

class Component {

public:
    virtual void draw() const = 0;
    virtual void tick() {};
    virtual void mouseDown(SDL_Event*) {};
    virtual ~Component();

protected:
    Component();
};


#endif
