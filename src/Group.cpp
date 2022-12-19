//
// Created by Anders Rydberg on 2022-12-08.
//

#include "Group.h"
#include "Component.h"


Group* Group::getInstance(World* world, const std::string& name) {
    return new Group(world, name);
}


Group::~Group() {
    for (Component* comp: comps)
        delete comp;
}

void Group::tick(GameEngine& engine) {
    for (Component* comp : comps)
        comp->tick(engine, this);

    _removeComponents();
    _addComponents();
}

void Group::checkCollisions(GameEngine& engine) {
    if (bCanCollideInternally) {
        for (Component* firstComp: comps) {
            for (Component* secondComp: comps) {
                if (firstComp != secondComp)
                    firstComp->checkCollision(engine, this, secondComp, this);
            }
        }
    }
}

void Group::checkCollisions(GameEngine& engine, Group* otherGroup) {
    if (bCanCollideExternally && otherGroup->bCanCollideExternally) {
        for (Component* internalComp: comps) {
            for (Component* externalComp: otherGroup->getContents())
                internalComp->checkCollision(engine, this, externalComp, otherGroup);
        }
    }
}


void Group::draw(GameEngine& engine) const {
    if (bVisible) {
        for (Component* comp: comps)
            comp->draw(engine);
    }
}

void Group::mouseDown(GameEngine& engine, SDL_Event* event) {
    for (Component* comp : comps)
        comp->mouseDown(engine, this, event);
}

void Group::add(Component *comp) {
    addQueue.push_back(comp);
}


void Group::add(Component* comp, const std::string& groupName) {
    world->add(comp, groupName);
}


void Group::remove(Component *comp) {
    removeQueue.push_back(comp);
}

void Group::move(Component* comp, const std::string& groupName) {
    removeQueue.push_back(comp);
    world->add(comp, groupName);
}



//// protected

void Group::_addComponents() {
    for (Component* comp : addQueue)
        comps.push_back(comp);
    addQueue.clear();
}

void Group::_removeComponents() {
    for (Component* comp : removeQueue) {
        for (auto iter = comps.begin();
             iter != comps.end(); iter++) {
            if (*iter == comp) {
                comps.erase(iter);
                delete comp;
                break; // inner for (continue with the next comp)
            }
        }
    }
    removeQueue.clear();
}

