//
// Created by Anders Rydberg on 2022-12-07.
//

#include "World.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Sprite.h"
#include "System.h"

void World::draw() const {
    for (Component* comp : comps)
        comp->draw();
}

void World::mouseDown(SDL_Event* event) {
    for (Component* comp : comps)
        comp->mouseDown(this, event);
}

void World::tick() {
    for (Component* comp : comps)
        comp->tick(this);

    // add any new components generated in the tick-loop
    addComponents();

    // remove any "dead" components, free memory
    removeComponents();
}

void World::addComponents() {
    for (Component* comp : addQueue)
        comps.push_back(comp);
    addQueue.clear();
}

void World::removeComponents() {
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


void World::add(Component *comp) {
    addQueue.push_back(comp);
}

void World::remove(Component *comp) {
    removeQueue.push_back(comp);
}

void World::setBackground(const std::string& filepath) {
    auto* background = new Sprite(filepath);
    add(background);
}
