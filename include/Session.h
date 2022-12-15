//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include "World.h"

class Session {

public:
    ~Session();
    static Session& getInstance(System& sys);

    void run();
    void quit() {bQuit = true;}

    World* getWorld() const {return world;}
    int getFPS() const {return fps;}

    void setFPS(int framesPerSecond) {fps = framesPerSecond;}

private:
    Session(System& sys);

    System& sys;

    bool bQuit {false};
    int fps {60};
    World* world;
};

#endif
