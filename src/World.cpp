//
// Created by Anders Rydberg on 2022-12-07.
//

#include "World.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Group.h"
#include "GameEngine.h"

using namespace std;

World::~World() {
    for (const auto& pair: groups)
        delete pair.second;
}

void World::tick() {
    for (const string& name : iterationOrder)
        groups.at(name)->tick(engine);
}

void World::checkCollisions() {
    for (const auto& groupNameFirst: iterationOrder) {
        Group* firstGroup = groups.find(groupNameFirst)->second;
        for (const auto& groupNameSecond: iterationOrder) {
            Group* secondGroup = groups.find(groupNameSecond)->second;
            if (firstGroup == secondGroup)
                firstGroup->checkCollisions(engine);
            else
                firstGroup->checkCollisions(engine, secondGroup);
        }
    }
}

void World::draw() const {
    for (const string& name: iterationOrder)
        groups.at(name)->draw(engine);
}

void World::mousePressed(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->mousePressed(engine, event);
}

void World::mouseReleased(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->mouseReleased(engine, event);
}

void World::mouseMoved(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->mouseMoved(engine, event);
}

void World::upKeyPressed(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->upKeyPressed(engine, event);
}

void World::downKeyPressed(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->downKeyPressed(engine, event);
}

void World::leftKeyPressed(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->leftKeyPressed(engine, event);
}

void World::rightKeyPressed(SDL_Event* event) {
    for (const string& name: iterationOrder)
        groups.at(name)->rightKeyPressed(engine, event);
}


/**
 * Adds component to group "group". If such a group does not yet exist,
 * an empty group with the specified name is first created.
 */
void World::add(Component* comp, const string& group) {
    auto iter = groups.find(group);
    if (iter == groups.end()) {
        Group* newGroup = addGroup(group);
        newGroup->add(comp);
    } else {
        iter->second->add(comp);
    }
}






//// public functions for group creation and manipulation

/// not queued (considered "tick-safe")
/**
 * Appends an empty group with the specified name to the end of the iteration order.
 * If such a group already exists, returns nullptr.
 */
Group* World::addGroup(const string& name) {
    if (groups.count(name) != 0)
        return nullptr;

    auto newGroup = Group::getInstance(this, name);
    iterationOrder.push_back(name);
    groups.insert(make_pair(name, newGroup));
    return newGroup;
}

void World::addGroup(Group* group) {
    const string& name = group->getName();
    if (groups.count(name) == 0) {
        iterationOrder.push_back(name);
        groups.insert(make_pair(name, group));
    }
}

/// queued (not safe to perform during iteration)
/**
 * Inserts an empty group with the specified "name" before the group "upper". If a group
 * "name" already exists, does nothing. If a group "upper" does not exist, appends the group
 * to the end of the iteration order.
 */
void World::addGroup(const string& name, const string& upper) {
    if (groups.count(name) == 0) {
        auto newGroup = Group::getInstance(this, name);
        addGroup(newGroup, upper);
    }
}

void World::addGroup(Group* group, const string& upper) {
    groupAddQueue.insert(make_pair(group, upper));
}


void World::removeGroup(const string& name) {
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
void World::mergeGroups(const string& first, const string& second) {
    auto iterFirst = groups.find(first);
    auto iterSecond = groups.find(second);
    if (iterFirst == groups.end() || iterSecond == groups.end())
        return;
    mergeGroups(iterFirst->second, iterSecond->second);
}

void World::mergeGroups(Group* first, const string& second) {
    auto iterSecond = groups.find(second);
    if (iterSecond != groups.end())
        mergeGroups(first, iterSecond->second);
}

void World::mergeGroups(Group *first, Group *second) {
    groupMergeQueue.insert(make_pair(first, second));
}

void World::message(const string& message, const string& group) {
    if (groups.count(group))
        groups[group]->message(message);
}

Group* World::getGroup(const string& groupName) {
    return groups.find(groupName)->second;
}




//// private

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

void World::_addGroups() {
    for (auto pair: groupAddQueue) {
        Group* group = pair.first;
        const string& name = group->getName();
        string& upper = pair.second;

        auto iter = iterationOrder.begin();
        for (; iter != iterationOrder.end(); iter++)
            if (*iter == upper) break;

        iterationOrder.insert(iter, name);
        groups.insert(make_pair(name, group));
    }
    groupAddQueue.clear();
}
