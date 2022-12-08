//
// Created by Anders Rydberg on 2022-12-07.
//

#include <SDL2/SDL_image.h>
#include "Map.h"
#include "Sprite.h"
#include "System.h"

void Map::draw() const {
    for (Component* comp : comps)
        comp->draw();
}

void Map::mouseDown(SDL_Event* event) {
    for (Component* comp : comps)
        comp->mouseDown(event);
}

void Map::tick() {
    for (Component* comp : comps)
        comp->tick();

    // add any new components generated in the tick-loop
    addComponents();

    // remove any "dead" components, free memory
    removeComponents();
}

void Map::addComponents() {
    for (Component* comp : addQueue)
        comps.push_back(comp);
    addQueue.clear();
}

void Map::removeComponents() {
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


void Map::add(Component *comp) {
    addQueue.push_back(comp);
}

void Map::remove(Component *comp) {
    removeQueue.push_back(comp);
}

void Map::setBackground(const std::string& filepath) {
    auto* background = new Sprite(filepath);

    add(background);

}
