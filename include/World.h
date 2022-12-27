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

using namespace std;

class Component;
class Group;
class GameEngine;

class World {

public:
    World(GameEngine& engine) : engine(engine) {}
    ~World();

    void tick();
    void checkCollisions();
    void draw() const;
    void mousePressed(SDL_Event* event);
    void mouseReleased(SDL_Event* event);
    void mouseMoved(SDL_Event* event);
    void upKeyPressed(SDL_Event* event);
    void downKeyPressed(SDL_Event* event);
    void leftKeyPressed(SDL_Event* event);
    void rightKeyPressed(SDL_Event* event);



    // adds component to group "group"
    void add(Component *comp, const string& group);

    // appends group to the end of the iteration order
    Group* addGroup(const string& name);
    void addGroup(Group* group);
    // inserts group before group "upper"
    void addGroup(const string& name, const string& upper);
    void addGroup(Group* group, const string& upper);

    void removeGroup(const string& name);
    void removeGroup(Group* group);

    // merges second group into first
    void mergeGroups(const string& first, const string& second);
    void mergeGroups(Group* first, const string& second);
    void mergeGroups(Group* first, Group* second);

    Group* getGroup(const string& groupName);



private:
    GameEngine& engine;

    list<string> iterationOrder;
    unordered_map<string, Group*> groups;

    unordered_map<Group*, string> groupAddQueue;
    vector<Group*> groupDeleteQueue;
    unordered_map<Group*, Group*> groupMergeQueue;

    void _addGroups();
    void _mergeGroups();
    void _removeGroups();

};


#endif
