//
// Created by Anders Rydberg on 2022-12-08.
//

#ifndef GROUP_H
#define GROUP_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "World.h"

class Component;

class Group {
public:
    static Group* getInstance(World* world, const std::string& name);
    virtual ~Group();
    Group(const Group& other) = delete;
    Group& operator=(const Group& other) = delete;

    virtual void tick(GameEngine& engine);
    // group-internal collision check
    virtual void checkCollisions(GameEngine& engine);
    // group-external collision check
    virtual void checkCollisions(GameEngine& engine, Group* otherGroup);
    virtual void draw(GameEngine& engine) const;
    virtual void mousePressed(GameEngine& engine, SDL_Event* event);
    virtual void mouseReleased(GameEngine& engine, SDL_Event* event);
    virtual void mouseMoved(GameEngine& engine, SDL_Event* event);
    virtual void upKeyPressed(GameEngine& engine, SDL_Event* event);
    virtual void downKeyPressed(GameEngine& engine, SDL_Event* event);
    virtual void leftKeyPressed(GameEngine& engine, SDL_Event* event);
    virtual void rightKeyPressed(GameEngine& engine, SDL_Event* event);


    virtual const std::string& getName() const {return name;}
    virtual std::vector<Component*>& getContents() {return comps;}

    bool bCanCollideInternally {true};
    bool bCanCollideExternally {true};
    bool bVisible {true};

    // add to this group
    virtual void add(Component* comp);
    // add to another group
    virtual void add(Component* comp, const std::string& groupName);
    virtual void remove(Component* comp);
    virtual void move(Component* comp, const std::string& groupName);

protected:
    Group(World* world, const std::string& name) : world(world), name(name) {}

    virtual void _addComponents();
    virtual void _removeComponents();

    World* world;
    std::string name;
    std::vector<Component*> comps;

    std::vector<Component*> addQueue;
    std::vector<Component*> removeQueue;

};


#endif
