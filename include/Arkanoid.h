//
// Created by Anders Rydberg on 2022-12-27.
//

#ifndef ARKANOID_H
#define ARKANOID_H

#include "Component.h"
#include "GameEngine.h"

const int windowW = 1024;
const int windowH = 720;

class SpriteSheet {
public:
    SpriteSheet(GameEngine& engine);
    ~SpriteSheet();

    SDL_Texture* getTexture() const;
    SDL_Rect bluePaddle4 {58, 302, 90, 30};

private:
    SDL_Texture* texture;
};


class Paddle : public Component {
public:
    Paddle(SpriteSheet* sheet, SDL_Rect* sRect, int x, int y, int w, int h);
    ~Paddle() override;
    void draw(GameEngine& engine) override;
    void mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) override;

private:
    SpriteSheet* sheet;
    SDL_Rect* sRect;
    SDL_Rect* dRect;
};


#endif
