//
// Created by Anders Rydberg on 2022-12-07.
//

#include "World.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Group.h"
#include "System.h"

void World::draw() const {
    for (const std::string& name : iterationOrder)
        groups.at(name)->draw();
}

void World::tick() {
    for (const std::string& name : iterationOrder)
        groups.at(name)->tick();
}

void World::mouseDown(SDL_Event* event) {
    for (const std::string& name : iterationOrder)
        groups.at(name)->mouseDown(event);
}


/**
 * Adds component to group "group". If such a group does not yet exist,
 * an empty group with the specified name is first created.
 */
void World::add(Component* comp, const std::string& group) {
    auto iter = groups.find(group);
    if (iter == groups.end()) {
        Group* newGroup = addGroup(group);
        newGroup->add(comp);
    } else {
        iter->second->add(comp);
    }
}


/**
 * Appends an empty group with the specified name to the end of the iteration order.
 * If such a group already exists, returns nullptr.
 */
Group* World::addGroup(const std::string& name) {
    if (groups.count(name) == 0)
        return nullptr;

    auto newGroup = new Group(this, name);
    iterationOrder.push_back(name);
    groups.insert(std::make_pair(name, newGroup));
    return newGroup;
}

/**
 * Inserts an empty group with the specified "name" before the group "upper". If a group
 * "name" already exists, returns nullptr. If a group "upper" does not exist, appends the group
 * to the end of the iteration order.
 */
Group* World::addGroup(const std::string& name, const std::string& upper) {
    if (groups.count(name) == 0)
        return nullptr;

    auto iter = iterationOrder.begin();
    for (; iter != iterationOrder.end(); iter++)
        if (*iter == upper) break;

    auto newGroup = new Group(this, name);
    iterationOrder.insert(iter, name);
    groups.insert(std::make_pair(name, newGroup));
}


void World::deleteGroup(const std::string& name) {
    auto iter = groups.find(name);
    if (iter == groups.end()) return;
    deleteGroup(iter->second);
}

void World::deleteGroup(Group* group) {
    groupDeleteQueue.push_back(group);
}

void World::mergeGroups(const std::string& first, const std::string& second) {

}

void World::mergeGroups(Group* first, const std::string& second) {

}

void World::mergeGroups(Group* first, Group* second) {

}



void World::deleteGroups() {
    for (Group* group: groupDeleteQueue) {
        auto comps= group->getContents();
        for (Component* comp: comps)
            delete comp;
        delete group;
    }
    groupDeleteQueue.clear();
}
