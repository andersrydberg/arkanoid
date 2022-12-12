//
// Created by Anders Rydberg on 2022-12-07.
//

#include "World.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Sprite.h"
#include "System.h"

void World::draw() const {
    for (std::string name : iterationOrder)
        groups.at(name)->draw();
}

void World::tick() {
    for (std::string name : iterationOrder)
        groups.at(name)->tick();
}

void World::mouseDown(SDL_Event* event) {
    for (std::string name : iterationOrder)
        groups.at(name)->mouseDown(event);
}



void World::add(Component *comp, const std::string &group) {

    addQueue.push_back(comp);
}

void World::removeGlobally(Component *comp) {
    removeQueue.push_back(comp);
}

void World::setBackground(const std::string& filepath) {
    auto* background = new Sprite(filepath);
    add(nullptr, background);
}
