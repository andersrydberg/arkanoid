//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <string>
#include "World.h"

using namespace std;

class GameEngine {

public:
    ~GameEngine();
    static GameEngine& getInstance(const string& title, int windowW, int windowH);

    void run();
    void quit();

    bool initWithErrors() const;

    int getWindowWidth() const {return windowW;}
    int getWindowHeight() const {return windowH;}
    const string& getTitle() const {return title;}

    void setTitle(const string& newTitle);

    SDL_Window* getWindow() const {return window;}
    SDL_Renderer* getRenderer() const {return rend;}
    World* getWorld() const {return world;}
    int getFPS() const {return fps;}

    void setFPS(int framesPerSecond) {fps = framesPerSecond;}

    void addShortcut(const string& key, void(* func)(World*, SDL_Event*));

    SDL_Texture* getTextureFromImage(const string& filepath);
    void drawTextureToRenderer(SDL_Texture* texture, SDL_Rect* rect);
    void drawTextureToRenderer(SDL_Texture* texture, SDL_Rect* sRect, SDL_Rect* dRect);


private:
    GameEngine(const string& title, int windowW, int windowH);
    bool init();

    string title;
    int windowW;
    int windowH;

    SDL_Window* window;
    SDL_Renderer* rend;

    World* world;

    bool bInitialized;

    bool bQuit {false};
    int fps {60};

    unordered_map<string, void (*)(World*, SDL_Event*)> functionMap;
};

#endif
