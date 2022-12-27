//
// Created by Anders Rydberg on 2022-12-08.
//

#ifndef GROUP_H
#define GROUP_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "World.h"

using namespace std;

class Component;

class Group {
public:
    static Group* getInstance(World* world, const string& name);
    static Group* getInstance(World* world, const string& name, bool collideInternally,
                              bool collideExternally, bool visible);
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


    virtual const string& getName() const {return name;}
    virtual vector<Component*>& getContents() {return comps;}

    bool bCanCollideInternally;
    bool bCanCollideExternally;
    bool bVisible;

    // add to this group
    virtual void add(Component* comp);
    // add to another group
    virtual void add(Component* comp, const string& groupName);
    virtual void remove(Component* comp);
    virtual void move(Component* comp, const string& groupName);

protected:
    Group(World* world, const string& name, bool collideInternally=true,
          bool collideExternally=true, bool visible=true);

    virtual void _addComponents();
    virtual void _removeComponents();

    World* world;
    string name;
    vector<Component*> comps;

    vector<Component*> addQueue;
    vector<Component*> removeQueue;

};


#endif
