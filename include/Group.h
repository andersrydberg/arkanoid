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
    virtual ~Group() = default;

    virtual void tick();
    virtual void draw() const;
    virtual void mouseDown(SDL_Event* event);

    const std::string& getName() const {return name;}
    bool canCollide() const {return bCanCollide;}

    void setCanCollide(bool value) {bCanCollide = value;}

    void add(Component* comp);

protected:
    Group(World* world, const std::string& name) : world(world), name(name) {}
    std::vector<Component*>& getContents() {return comps;}

    virtual void addComponents();
    virtual void removeComponents();

private:
    World* world;
    std::string name;
    std::vector<Component*> comps;

    std::vector<Component*> addQueue;
    std::vector<Component*> removeQueue;

    bool bCanCollide {true};
};


#endif
