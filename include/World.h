//
// Created by Anders Rydberg on 2022-12-07.
//

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <list>
#include <vector>
#include <utility>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "GameEngine.h"

class Component;
class Group;

class World {

public:
    World(GameEngine& sys) : sys(sys) {}
    ~World();

    void tick(GameEngine& sys);
    void draw(GameEngine& sys) const;
    void mouseDown(GameEngine& sys, SDL_Event* event);

    // adds component to group "group"
    void add(Component *comp, const std::string& group);

    // appends group to the end of the iteration order
    Group* addGroup(const std::string& name);
    // inserts group before group "upper"
    Group* addGroup(const std::string& name, const std::string& upper);

    void removeGroup(const std::string& name);
    void removeGroup(Group* group);

    // merges second group into first
    void mergeGroups(const std::string& first, const std::string& second);
    void mergeGroups(Group* first, const std::string& second);
    void mergeGroups(Group* first, Group* second);



private:
    GameEngine& sys;

    std::list<std::string> iterationOrder;
    std::unordered_map<std::string, Group*> groups;

    std::vector<Group*> groupDeleteQueue;
    std::vector<std::pair<Group*, Group*>> groupMergeQueue;

    void _addGroups();
    void _mergeGroups();
    void _removeGroups();

};


#endif
