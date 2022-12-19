//
// Created by Anders Rydberg on 2022-12-07.
//

#include "World.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Group.h"
#include "GameEngine.h"

World::~World() {
    for (const auto& pair: groups)
        delete pair.second;
}

void World::draw() const {
    for (const std::string& name : iterationOrder)
        groups.at(name)->draw(engine);
}

void World::tick() {
    for (const std::string& name : iterationOrder)
        groups.at(name)->tick(engine);
}

void World::mouseDown(SDL_Event* event) {
    for (const std::string& name : iterationOrder)
        groups.at(name)->mouseDown(engine, event);
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
    if (groups.count(name) != 0)
        return nullptr;

    auto newGroup = Group::getInstance(this, name);
    iterationOrder.push_back(name);
    groups.insert(std::make_pair(name, newGroup));
    return newGroup;
}

void World::addGroup(Group* group) {

}

void World::addGroup(Group* group, const std::string& upper) {

}

/**
 * Inserts an empty group with the specified "name" before the group "upper". If a group
 * "name" already exists, returns nullptr. If a group "upper" does not exist, appends the group
 * to the end of the iteration order.
 */
Group* World::addGroup(const std::string& name, const std::string& upper) {
    if (groups.count(name) != 0)
        return nullptr;

    auto iter = iterationOrder.begin();
    for (; iter != iterationOrder.end(); iter++)
        if (*iter == upper) break;

    auto newGroup = Group::getInstance(this, name);
    iterationOrder.insert(iter, name);
    groups.insert(std::make_pair(name, newGroup));
    return newGroup;
}


void World::removeGroup(const std::string& name) {
    auto iter = groups.find(name);
    if (iter == groups.end()) return;
    removeGroup(iter->second);
}

void World::removeGroup(Group* group) {
    groupDeleteQueue.push_back(group);
}


/**
 * Merges the second group into the first. If any or both of these are missing,
 * does nothing.
 */
void World::mergeGroups(const std::string& first, const std::string& second) {
    auto iterFirst = groups.find(first);
    auto iterSecond = groups.find(second);
    if (iterFirst == groups.end() || iterSecond == groups.end())
        return;
    mergeGroups(iterFirst->second, iterSecond->second);
}

void World::mergeGroups(Group* first, const std::string& second) {
    auto iterSecond = groups.find(second);
    if (iterSecond == groups.end()) return;
    mergeGroups(first, iterSecond->second);
}

void World::mergeGroups(Group *first, Group *second) {
    groupMergeQueue.emplace_back(first, second);
}


void World::_mergeGroups() {
    for (auto pair: groupMergeQueue) {
        auto firstVector = pair.first->getContents();
        auto secondVector = pair.second->getContents();
        for (Component *comp: secondVector)
            firstVector.push_back(comp);
        secondVector.clear();

        groups.erase(pair.second->getName());
        iterationOrder.remove(pair.second->getName());
        delete pair.second;
    }
    groupMergeQueue.clear();
}


void World::_removeGroups() {
    for (Group* group: groupDeleteQueue) {
        groups.erase(group->getName());
        iterationOrder.remove(group->getName());
        delete group;
    }
    groupDeleteQueue.clear();
}
