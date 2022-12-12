//
// Created by Anders Rydberg on 2022-12-07.
//

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "Group.h"

class Component;

class World {

public:
    void tick();
    void draw() const;

    void add(Component *comp, const std::string &group);
    void removeGlobally(Component* comp);


    void mouseDown(SDL_Event* event);

    void setBackground(const std::string& filepath);

private:
    World() = default;

    std::vector<std::string> iterationOrder;
    std::unordered_map<std::string, Group*> groups;

};


#endif
