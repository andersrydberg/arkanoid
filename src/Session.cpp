//
// Created by Anders Rydberg on 2022-11-21.
//

#include <SDL2/SDL.h>
#include "GameEngine.h"
#include "Session.h"
#include <iostream>

Session::Session(GameEngine& sys) : sys(sys) {
    world = new World(sys);
}

Session::~Session() {
    delete world;
}

