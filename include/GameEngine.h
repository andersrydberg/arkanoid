//
// Created by Anders Rydberg on 2022-11-15.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
#include "World.h"
#include "Component.h"

class GameEngine {

public:
    ~GameEngine();
    static GameEngine* initialize(const std::string& title, int windowW, int windowH);

    void run();
    void quit();

    int getWindowWidth() const {return windowW;}
    int getWindowHeight() const {return windowH;}
    const std::string& getTitle() const {return title;}

    void setTitle(const std::string& newTitle);

    SDL_Window* getWindow() const {return window;}
    SDL_Renderer* getRenderer() const {return rend;}
    World* getWorld() const {return world;}
    int getFPS() const {return fps;}
    long int getTickCount() const {return tickCount;}


    void setFPS(int framesPerSecond) {fps = framesPerSecond;}

    void addShortcut(const std::string& key, void(* func)(World*, SDL_Event*));

    SDL_Texture* getTextureFromImage(const std::string& filepath);
    void drawTextureToRenderer(SDL_Texture* texture, SDL_Rect* rect);
    void drawTextureToRenderer(SDL_Texture* texture, SDL_Rect* sRect, SDL_Rect* dRect);
    bool componentsIntersect(Component* first, Component* second);

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

    long int tickCount;

    std::unordered_map<std::string, void (*)(World*, SDL_Event*)> functionMap;

};


class sdl_initialization_error : public std::runtime_error {
public:
    explicit sdl_initialization_error(const std::string& what_arg="SDL could not be properly initialized")
    : std::runtime_error(what_arg) {}
};

#endif
