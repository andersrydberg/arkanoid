//
// Created by Anders Rydberg on 2022-12-27.
//

#ifndef ARKANOID_H
#define ARKANOID_H

#include "Component.h"
#include "GameEngine.h"
#include "SDL2/SDL.h"

const int windowW = 1024;
const int windowH = 720;

class SpriteSheet {
public:
    SpriteSheet(GameEngine& engine);
    ~SpriteSheet();

    SDL_Texture* getTexture() const;
    SDL_Rect ball1x1 {32, 128, 16, 16};
    SDL_Rect bluePaddle4 {58, 302, 90, 30};

private:
    SDL_Texture* texture;
};


class SpriteFromSheet : public Component {
public:
    SpriteFromSheet(SpriteSheet* sheet, SDL_Rect* sRect, int x, int y);
    SpriteFromSheet(SpriteSheet* sheet, SDL_Rect* sRect, int x, int y, int w, int h);
    ~SpriteFromSheet() override;
    void draw(GameEngine& engine) override;

protected:
    SpriteSheet* sheet;
    SDL_Rect* sRect;
    SDL_Rect* dRect;
};


class Paddle : public SpriteFromSheet {
public:
    using SpriteFromSheet::SpriteFromSheet;
    friend class Ball;
    void mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) override;
};


class Ball : public SpriteFromSheet {
public:
    Ball(SpriteSheet* sheet, SDL_Rect* sRect, Paddle* paddle);
    void mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) override;
    void mousePressed(GameEngine& engine, Group* group, SDL_Event* event) override;

private:
    Paddle* paddle;     // not used after the ball is released
    bool bReleased {false};
};

#endif
