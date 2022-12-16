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
    Component(const Component& other) = delete;
    Component& operator=(const Component& other) = delete;

    virtual void draw(GameEngine& engine) = 0;
    virtual void tick(GameEngine& engine, Group *group) {};

    virtual void mouseDown(GameEngine& engine, Group *group, SDL_Event *event) {};

protected:
    Component() = default;
};


#endif
