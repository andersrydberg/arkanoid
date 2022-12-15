//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include "Group.h"


class Component {

public:
    virtual ~Component() = default;

    virtual void draw(GameEngine& sys) = 0;
    virtual void tick(GameEngine& sys, Group *group) {};

    virtual void mouseDown(GameEngine& sys, Group *group, SDL_Event *event) {};

    bool bRemove {false};   // perhaps not needed

protected:
    Component() = default;
};


#endif
