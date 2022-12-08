//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Component.h"
#include "Map.h"

class Session {

public:
    Session();
    ~Session();
    void run();

    Map* getMap() const {return map;}

private:
    Map* map;
};

extern Session ses;


#endif
