//
// Created by Anders Rydberg on 2022-12-08.
//

#include "Group.h"
#include "Component.h"


Group::~Group() {
    for (Component* comp: comps)
        delete comp;
}


void Group::tick() {
    for (Component* comp : comps)
        comp->tick(this);

    removeComponents();
    addComponents();
}

void Group::draw() const {
    if (bVisible) {
        for (Component* comp: comps)
            comp->draw();
    }
}

void Group::mouseDown(SDL_Event *event) {
    for (Component* comp : comps)
        comp->mouseDown(this, event);
}

void Group::add(Component *comp) {
    addQueue.push_back(comp);
}

void Group::add(Component* comp, const std::string& name) {
    world->add(comp, name);
}


void Group::remove(Component *comp) {
    removeQueue.push_back(comp);
}


void Group::addComponents() {
    for (Component* comp : addQueue)
        comps.push_back(comp);
    addQueue.clear();
}

void Group::removeComponents() {
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

