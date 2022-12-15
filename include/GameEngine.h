//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <string>
#include "World.h"


class GameEngine {

public:
    ~GameEngine();
    static void initialize(const std::string&, int windowW, int windowH);
    static GameEngine& getInstance(const std::string& title, int windowW, int windowH);


    bool initWithErrors() const;

    int getWindowWidth() const;
    int getWindowHeight() const;

    void setTitle(const std::string& title) const;
    void run();

    void quit() {bQuit = true;}

    World* getWorld() const {return world;}
    int getFPS() const {return fps;}

    void setFPS(int framesPerSecond) {fps = framesPerSecond;}




private:
    GameEngine(const std::string& title, int windowW, int windowH);
    static int init(const std::string& title, int windowW, int windowH);

    SDL_Window* window;
    SDL_Renderer* rend;

    World* world;

    static bool bInitWithErrors;

    bool bQuit {false};
    int fps {60};

};

#endif
