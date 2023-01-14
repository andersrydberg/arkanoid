//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include "Group.h"

/**
 * Base class for all visual components.
 */
class Component {

public:
    virtual ~Component() = default;
    Component(const Component& other) = delete;
    Component& operator=(const Component& other) = delete;

    virtual void tick(GameEngine* engine, Group *group) {}
    virtual void checkCollision(GameEngine* engine, Group* group, Component* other, Group* otherGroup) {}
    virtual void draw(GameEngine* engine) {}
    virtual void receiveMessage(Group* group, const std::string& message) {}

    virtual void mousePressed(GameEngine* engine, Group* group, SDL_Event* event) {}
    virtual void mouseReleased(GameEngine* engine, Group* group, SDL_Event* event) {}
    virtual void mouseMoved(GameEngine* engine, Group* group, SDL_Event* event) {}
    virtual void upKeyPressed(GameEngine* engine, Group* group, SDL_Event* event) {}
    virtual void downKeyPressed(GameEngine* engine, Group* group, SDL_Event* event) {}
    virtual void leftKeyPressed(GameEngine* engine, Group* group, SDL_Event* event) {}
    virtual void rightKeyPressed(GameEngine* engine, Group* group, SDL_Event* event) {}

    virtual SDL_Rect* getDRect() = 0;

protected:
    Component() = default;
};


#endif
