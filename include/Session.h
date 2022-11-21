//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Component.h"

class Session {

public:
    void run();
    void add(Component* comp);
    void remove(Component* comp);


private:
    std::vector<Component*> comps;
    std::vector<Component*> addQueue;
    std::vector<Component*> removeQueue;
};


#endif
