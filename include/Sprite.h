//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include "Component.h"

class Sprite : public Component {

public:
    ~Sprite() override;
    static Sprite* getInstance();
    static Sprite* getInstance(GameEngine& engine, const std::string& filepath);
    static Sprite* getInstance(GameEngine& engine, const std::string& filepath, int x, int y, int w, int h);

    void draw(GameEngine& engine) override;

    bool bCanCollide {true};
    bool bVisible {true};

protected:
    Sprite();
    Sprite(GameEngine& engine, const std::string& filepath);
    Sprite(GameEngine& engine, const std::string& filepath, int x, int y, int w, int h);

    SDL_Rect* rect;
    SDL_Texture* texture;
};


#endif
