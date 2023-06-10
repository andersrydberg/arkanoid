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

class Group
{
public:
    static Group *getInstance(World *world, const std::string &name);
    static Group *getInstance(World *world, const std::string &name, bool collideInternally,
                              bool collideExternally, bool visible);
    virtual ~Group();
    Group(const Group &other) = delete;
    Group &operator=(const Group &other) = delete;

    virtual void tick(GameEngine *engine);
    // group-internal collision check
    virtual void checkCollisions(GameEngine *engine);
    // group-external collision check
    virtual void checkCollisions(GameEngine *engine, Group *otherGroup);
    virtual void draw(GameEngine *engine) const;
    virtual void mousePressed(GameEngine *engine, SDL_Event *event);
    virtual void mouseReleased(GameEngine *engine, SDL_Event *event);
    virtual void mouseMoved(GameEngine *engine, SDL_Event *event);
    virtual void upKeyPressed(GameEngine *engine, SDL_Event *event);
    virtual void downKeyPressed(GameEngine *engine, SDL_Event *event);
    virtual void leftKeyPressed(GameEngine *engine, SDL_Event *event);
    virtual void rightKeyPressed(GameEngine *engine, SDL_Event *event);

    virtual const std::string &getName() const { return name; }
    virtual std::vector<Component *> &getContents() { return comps; }

    bool canCollideInternally() const { return bCanCollideInternally; }
    bool canCollideExternally() const { return bCanCollideExternally; }
    bool isVisible() const { return bVisible; }

    virtual void setCollideInternally(bool value);
    virtual void setCollideExternally(bool value);
    virtual void setVisible(bool value);

    // add to this group
    virtual void add(Component *comp);
    // add to another group
    virtual void add(Component *comp, const std::string &groupName);
    virtual void remove(Component *comp);
    virtual void move(Component *comp, const std::string &groupName);

    // message members of this group
    virtual void message(const std::string &message);
    // message members of named group
    virtual void message(const std::string &message, const std::string &group);

protected:
    Group(World *world, const std::string &name, bool collideInternally = true,
          bool collideExternally = true, bool visible = true);

    virtual void _addComponents();
    virtual void _removeComponents();

    World *getWorld() { return world; }

private:
    bool bCanCollideInternally;
    bool bCanCollideExternally;
    bool bVisible;

    World *world;
    std::string name;
    std::vector<Component *> comps;

    std::vector<Component *> addQueue;
    std::vector<Component *> removeQueue;
};

#endif
