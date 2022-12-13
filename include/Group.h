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
    friend class World;
    virtual ~Group();
    Group(const Group& other) = delete;
    Group& operator=(const Group& other) = delete;

    virtual void tick();
    virtual void draw() const;
    virtual void mouseDown(SDL_Event* event);

    const std::string& getName() const {return name;}
    std::vector<Component*>& getContents() {return comps;}

    bool bCanCollide {true};
    bool bVisible {true};

    // add to this group
    void add(Component* comp);
    // add to another group
    void add(Component* comp, const std::string& name);
    void remove(Component* comp);

protected:
    Group(World* world, const std::string& name) : world(world), name(name) {}

    virtual void addComponents();
    virtual void removeComponents();

    World* world;
    std::string name;
    std::vector<Component*> comps;

    std::vector<Component*> addQueue;
    std::vector<Component*> removeQueue;

};


#endif
