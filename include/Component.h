//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include "Group.h"


class Component {

public:
    virtual void draw() = 0;
    virtual void tick(Group *group) {};
    virtual void mouseDown(Group *group, SDL_Event *event) {};
    virtual ~Component();

    bool bRemove {false};   // perhaps not needed

protected:
    Component();
};


#endif
