//
// Created by Anders Rydberg on 2022-12-27.
//

#include "Arkanoid.h"
#include "GameEngine.h"
#include "Constants.h"
#include "SDL2/SDL.h"


//// SpriteSheet

SpriteSheet::SpriteSheet(GameEngine& engine) {
    texture = engine.getTextureFromImage(constants::gResPath + constants::spriteSheetRelPath);
}

SpriteSheet::~SpriteSheet() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* SpriteSheet::getTexture() const {
    return texture;
}


/// SpriteFromSheet

SpriteFromSheet::SpriteFromSheet(SpriteSheet* sheet, const SDL_Rect* sourceRect, int x, int y)
: SpriteFromSheet(sheet, sourceRect, x, y, sourceRect->w, sourceRect->h) {
}

SpriteFromSheet::SpriteFromSheet(SpriteSheet* sheet, const SDL_Rect* sourceRect, int x, int y, int w, int h)
: sheet(sheet) {
    sRect = sourceRect ? new SDL_Rect(*sourceRect) : nullptr;
    dRect = new SDL_Rect {x, y, w, h};
}

SpriteFromSheet::~SpriteFromSheet() {
    delete sRect;
    delete dRect;
}

void SpriteFromSheet::draw(GameEngine& engine) {
    engine.drawTextureToRenderer(sheet->getTexture(), sRect, dRect);
}


//// Paddle

void Paddle::mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) {
    int newX = event->motion.x - dRect->w / 2;     // align mouse to the center of the paddle
    int maxX = windowW - dRect->w;

    if (newX < 0)
        dRect->x = 0;
    else if (newX > maxX)
        dRect->x = maxX;
    else
        dRect->x = newX;
}


//// Ball

Ball::Ball(SpriteSheet* sheet, const SDL_Rect* sourceRect, Paddle* paddle)
: SpriteFromSheet(sheet, sourceRect, paddle->dRect->x + 20, paddle->dRect->y - sourceRect->h), paddle(paddle) {
}

void Ball::mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) {
    if (!bReleased) {
        dRect->x = paddle->dRect->x + 20;
    }
}

void Ball::mousePressed(GameEngine& engine, Group* group, SDL_Event* event) {
    if (!bReleased) {
        velocity = 10.0;
        double initialAngle = PI * 1.75;
        xVel = velocity * cos(initialAngle);
        yVel = velocity * sin(initialAngle);
        bReleased = true;
    }
}

void Ball::tick(GameEngine& engine, Group* group) {
    dRect->x += static_cast<int>(std::round(xVel));
    dRect->y += static_cast<int>(std::round(yVel));
}