//
// Created by Anders Rydberg on 2022-12-07.
//

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Component;

class World {

public:
    void tick();
    void draw() const;
    void add(Component* comp);
    void remove(Component* comp);
    void mouseDown(SDL_Event* event);

    void setBackground(const std::string& filepath);

private:
    void addComponents();
    void removeComponents();

    std::vector<Component*> comps;
    std::vector<Component*> addQueue;
    std::vector<Component*> removeQueue;

};


#endif
