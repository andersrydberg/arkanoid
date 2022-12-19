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
    virtual void mouseDown(GameEngine& engine, SDL_Event* event);

    const std::string& getName() const {return name;}
    std::vector<Component*>& getContents() {return comps;}

    bool bCanCollideInternally {true};
    bool bCanCollideExternally {true};
    bool bVisible {true};

    // add to this group
    void add(Component* comp);
    // add to another group
    void add(Component* comp, const std::string& groupName);
    void remove(Component* comp);
    void move(Component* comp, const std::string& groupName);

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
