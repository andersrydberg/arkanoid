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
    static GameEngine& getInstance(const std::string& title, int windowW, int windowH);

    void run();
    void quit();

    bool initWithErrors() const;

    int getWindowWidth() const {return windowW;}
    int getWindowHeight() const {return windowH;}
    const std::string& getTitle() const {return title;}

    void setTitle(const std::string& newTitle);

    SDL_Window* getWindow() const {return window;}
    SDL_Renderer* getRenderer() const {return rend;}
    World* getWorld() const {return world;}
    int getFPS() const {return fps;}

    void setFPS(int framesPerSecond) {fps = framesPerSecond;}




private:
    GameEngine(const std::string& title, int windowW, int windowH);
    bool init();

    std::string title;
    int windowW;
    int windowH;

    SDL_Window* window;
    SDL_Renderer* rend;

    World* world;

    bool bInitialized;

    bool bQuit {false};
    int fps {60};

};

#endif
