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

SpriteFromSheet::SpriteFromSheet(SpriteSheet* sheet, SDL_Rect* sRect, int x, int y)
: SpriteFromSheet(sheet, sRect, x, y, sRect->w, sRect->h) {
}

SpriteFromSheet::SpriteFromSheet(SpriteSheet* sheet, SDL_Rect* sRect, int x, int y, int w, int h)
: sheet(sheet), sRect(sRect) {
    dRect = new SDL_Rect {x, y, w, h};
}

SpriteFromSheet::~SpriteFromSheet() {
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

Ball::Ball(SpriteSheet* sheet, SDL_Rect* sRect, Paddle* paddle)
: SpriteFromSheet(sheet, sRect, paddle->dRect->x + 20, paddle->dRect->y - sRect->h), paddle(paddle) {
}

void Ball::mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) {
    if (!bReleased) {
        dRect->x = paddle->dRect->x + 20;
    }
}

void Ball::mousePressed(GameEngine& engine, Group* group, SDL_Event* event) {
    if (!bReleased) {
        bReleased = true;
    }
}
