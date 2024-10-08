//
// Created by Anders Rydberg on 2022-12-08.
//

#include "Group.h"
#include "Component.h"

using namespace std;

Group *Group::getInstance(World *world, const string &name)
{
    return new Group(world, name);
}

Group *Group::getInstance(World *world, const string &name, bool collideInternally, bool collideExternally,
                          bool visible)
{
    return new Group(world, name, collideInternally, collideExternally, visible);
}

Group::Group(World *world, const string &name, bool collideInternally, bool collideExternally, bool visible)
    : bCanCollideInternally(collideInternally), bCanCollideExternally(collideExternally), bVisible(visible), world(world),
      name(name)
{
}

Group::~Group()
{
    for (Component *comp : comps)
        delete comp;
}

void Group::tick(GameEngine *engine)
{
    for (Component *comp : comps)
        comp->tick(engine, this);

    _removeComponents();
    _addComponents();
}

/*
Collision checking functions do not actually check if the objects called as parameters have
collided, this is left to the programmer. Use e.g. GameEngine.componentsIntersect to check if
two objects overlap */

void Group::checkCollisions(GameEngine *engine)
{
    if (bCanCollideInternally)
    {
        for (Component *firstComp : comps)
        {
            for (Component *secondComp : comps)
            {
                if (firstComp != secondComp)
                    firstComp->checkCollision(engine, this, secondComp, this);
            }
        }
    }
}

void Group::checkCollisions(GameEngine *engine, Group *otherGroup)
{
    if (bCanCollideExternally && otherGroup->bCanCollideExternally)
    {
        for (Component *internalComp : comps)
        {
            for (Component *externalComp : otherGroup->getContents())
                internalComp->checkCollision(engine, this, externalComp, otherGroup);
        }
    }
}

void Group::draw(GameEngine *engine) const
{
    if (bVisible)
    {
        for (Component *comp : comps)
            comp->draw(engine);
    }
}

void Group::mousePressed(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->mousePressed(engine, this, event);
}

void Group::mouseReleased(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->mouseReleased(engine, this, event);
}

void Group::mouseMoved(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->mouseMoved(engine, this, event);
}

void Group::upKeyPressed(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->upKeyPressed(engine, this, event);
}

void Group::downKeyPressed(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->downKeyPressed(engine, this, event);
}

void Group::leftKeyPressed(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->leftKeyPressed(engine, this, event);
}

void Group::rightKeyPressed(GameEngine *engine, SDL_Event *event)
{
    for (Component *comp : comps)
        comp->rightKeyPressed(engine, this, event);
}

void Group::setCollideInternally(bool value)
{
    bCanCollideInternally = value;
}

void Group::setCollideExternally(bool value)
{
    bCanCollideExternally = value;
}

void Group::setVisible(bool value)
{
    bVisible = value;
}

void Group::add(Component *comp)
{
    addQueue.push_back(comp);
}

void Group::add(Component *comp, const string &groupName)
{
    world->add(comp, groupName);
}

void Group::remove(Component *comp)
{
    removeQueue.push_back(comp);
}

void Group::move(Component *comp, const string &groupName)
{
    removeQueue.push_back(comp);
    world->add(comp, groupName);
}

void Group::message(const string &message)
{
    for (Component *comp : comps)
        comp->receiveMessage(this, message);
}

void Group::message(const string &message, const string &group)
{
    world->message(message, group);
}

//// protected

void Group::_addComponents()
{
    for (Component *comp : addQueue)
        comps.push_back(comp);
    addQueue.clear();
}

void Group::_removeComponents()
{
    for (Component *comp : removeQueue)
    {
        for (auto iter = comps.begin();
             iter != comps.end(); iter++)
        {
            if (*iter == comp)
            {
                comps.erase(iter);
                delete comp;
                break; // inner for (continue with the next comp)
            }
        }
    }
    removeQueue.clear();
}
