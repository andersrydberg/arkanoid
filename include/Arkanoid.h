//
// Created by Anders Rydberg on 2022-12-27.
//

#ifndef ARKANOID_H
#define ARKANOID_H

#include "GameEngine.h"
#include "SpriteSheet.h"
#include "SpriteFromSheet.h"
#include <SDL.h>
#include <random>

constexpr double PI = 3.14159265359;

constexpr int WINDOW_W = 1024;
constexpr int WINDOW_H = 692;

constexpr int BRICK_PIXEL_WIDTH = 54;
constexpr int BRICK_PIXEL_HEIGHT = 22;

constexpr SDL_Rect ball0x0{32, 128, 16, 16};
constexpr SDL_Rect bluePaddle4{58, 302, 90, 30};
constexpr SDL_Rect vertSilverWall{190, 148, 18, 56};
constexpr SDL_Rect vertSilverWallUpperHalf{190, 148, 18, 28};
constexpr SDL_Rect vertSilverWallLowerHalf{190, 176, 18, 28};
constexpr SDL_Rect horSilverWall{190, 204, 56, 18};
constexpr SDL_Rect horSilverWallLeftHalf{190, 204, 28, 18};
constexpr SDL_Rect silverWallCorner0x0{134, 148, 20, 20};
constexpr SDL_Rect silverWallCorner1x0{170, 148, 20, 20};
constexpr SDL_Rect blueBrick1{324, 22, 54, 22};


class Wall : public SpriteFromSheet
{
public:
    Wall(SpriteSheet *sheet, const SDL_Rect *sourceRect, int x, int y, int x_factor, int y_factor);
    // determine ball bounce direction
    const int x_factor;
    const int y_factor;
};

class Brick : public SpriteFromSheet
{
public:
    Brick(SpriteSheet *sheet, int x, int y);
    void checkCollision(Group *group, Component *other, Group *otherGroup) override;
    void tick(GameEngine *engine, Group *group) override;

private:
    bool bCollided{false};
    int counter{0};
};

class Paddle : public SpriteFromSheet
{
public:
    Paddle(SpriteSheet *sheet, int x, int y);
    void mouseMoved(GameEngine *engine, Group *group, SDL_Event *event) override;
    void receiveMessage(Group *group, const std::string &message) override;

private:
    bool bBallReleased{false};
};

class Ball : public SpriteFromSheet
{
public:
    Ball(SpriteSheet *sheet, int x, int y);
    void mousePressed(GameEngine *engine, Group *group, SDL_Event *event) override;
    void tick(GameEngine *engine, Group *group) override;
    void receiveMessage(Group *group, const std::string &message) override;
    void checkCollision(Group *group, Component *other, Group *otherGroup) override;

private:
    bool bReleased{false};
    bool bCollided{false};
    double velocity, xVel, yVel{0.0};
};

#endif
