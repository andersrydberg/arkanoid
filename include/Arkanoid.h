//
// Created by Anders Rydberg on 2022-12-27.
//

#ifndef ARKANOID_H
#define ARKANOID_H

#include "Component.h"
#include "GameEngine.h"
#include "SDL2/SDL.h"

const int windowW = 1024;
const int windowH = 692;
const double PI = 4 * atan(1);

class SpriteSheet {
public:
    SpriteSheet(GameEngine& engine);
    ~SpriteSheet();

    SDL_Texture* getTexture() const;
    const SDL_Rect ball0x0 {32, 128, 16, 16};
    const SDL_Rect bluePaddle4 {58, 302, 90, 30};
    const SDL_Rect vertSilverWall {190, 148, 18, 56};
    const SDL_Rect vertSilverWallUpperHalf {190, 148, 18, 28};
    const SDL_Rect vertSilverWallLowerHalf {190, 176, 18, 28};

    const SDL_Rect horSilverWall {190, 204, 56, 18};
    const SDL_Rect horSilverWallLeftHalf {190, 204, 28, 18};
    const SDL_Rect horSilverWallRightHalf {218, 204, 28, 18};
    const SDL_Rect silverWallCorner0x0 {134, 148, 20,20};
    const SDL_Rect silverWallCorner1x0 {170, 148, 20,20};
    const SDL_Rect silverWallCorner0x1 {134, 198, 20,20};
    const SDL_Rect silverWallCorner1x1 {170, 198, 20,20};

private:
    SDL_Texture* texture;
};


class SpriteFromSheet : public Component {
public:
    SpriteFromSheet(SpriteSheet* sheet, const SDL_Rect* sourceRect, int x, int y);
    SpriteFromSheet(SpriteSheet* sheet, const SDL_Rect* sourceRect, int x, int y, int w, int h);
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
    Ball(SpriteSheet* sheet, const SDL_Rect* sourceRect, Paddle* paddle);
    void mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) override;
    void mousePressed(GameEngine& engine, Group* group, SDL_Event* event) override;
    void tick(GameEngine& engine, Group* group) override;

private:
    Paddle* paddle;     // not used after the ball is released
    bool bReleased {false};
    double velocity, xVel, yVel {0.0};
};

#endif
