//
// Created by Anders Rydberg on 2022-12-07.
//

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>

class Component;
class Group;

class World {

public:
    void tick();
    void draw() const;

    // adds component to group "group"
    void add(Component *comp, const std::string& group);

    // appends group to the end of the iteration order
    Group* addGroup(const std::string& name);
    // inserts group before group "upper"
    Group* addGroup(const std::string& name, const std::string& upper);

    // removes and deletes all components before removing and deleting the group
    void deleteGroup(const std::string& name);
    void deleteGroup(Group* group);

    // merges second group into first
    void mergeGroups(const std::string& first, const std::string& second);
    void mergeGroups(Group* first, const std::string& second);
    void mergeGroups(Group* first, Group* second);

    void mouseDown(SDL_Event* event);


private:
    World() = default;

    std::vector<std::string> iterationOrder;
    std::unordered_map<std::string, Group*> groups;

    std::vector<Group*> groupDeleteQueue;

    void deleteGroups();

};


#endif
