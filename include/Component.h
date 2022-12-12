//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

class World;

class Component {

public:
    virtual void draw() = 0;
    virtual void tick(World* world) {};
    virtual void mouseDown(World* world, SDL_Event*) {};
    virtual ~Component();

    bool bRemove {false};

protected:
    Component();
};


#endif
