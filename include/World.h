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

class Component;
class Group;
class GameEngine;

class World
{

public:
    World(GameEngine *engine) : engine(engine) {}
    ~World();

    void tick();
    void checkCollisions();
    void draw() const;
    void mousePressed(SDL_Event *event);
    void mouseReleased(SDL_Event *event);
    void mouseMoved(SDL_Event *event);
    void upKeyPressed(SDL_Event *event);
    void downKeyPressed(SDL_Event *event);
    void leftKeyPressed(SDL_Event *event);
    void rightKeyPressed(SDL_Event *event);

    // adds component to group "group"
    void add(Component *comp, const std::string &group);

    // appends group to the end of the iteration order
    Group *addGroup(const std::string &name);
    void addGroup(Group *group);
    // inserts group before group "upper"
    void addGroup(const std::string &name, const std::string &upper);
    void addGroup(Group *group, const std::string &upper);

    void removeGroup(const std::string &name);
    void removeGroup(Group *group);

    // merges second group into first
    void mergeGroups(const std::string &first, const std::string &second);
    void mergeGroups(Group *first, const std::string &second);
    void mergeGroups(Group *first, Group *second);

    // messages all members of named group
    void message(const std::string &message, const std::string &group);

    Group *getGroup(const std::string &groupName);

private:
    GameEngine *engine;

    std::list<std::string> iterationOrder;
    std::unordered_map<std::string, Group *> groups;

    std::unordered_map<Group *, std::string> groupAddQueue;
    std::vector<Group *> groupDeleteQueue;
    std::unordered_map<Group *, Group *> groupMergeQueue;

    void _addGroups();
    void _mergeGroups();
    void _removeGroups();
};

#endif
