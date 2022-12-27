//
// Created by Anders Rydberg on 2022-12-27.
//

#include "Arkanoid.h"
#include "GameEngine.h"
#include "Constants.h"

SpriteSheet::SpriteSheet(GameEngine& engine) {
    texture = engine.getTextureFromImage(constants::gResPath + constants::spriteSheetRelPath);
}

SpriteSheet::~SpriteSheet() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* SpriteSheet::getTexture() const {
    return texture;
}

Paddle::Paddle(SpriteSheet* sheet, SDL_Rect* sRect, int x, int y, int w, int h): sheet(sheet), sRect(sRect) {
    dRect = new SDL_Rect {x, y, w, h};
}

Paddle::~Paddle() {
    delete dRect;
}

void Paddle::draw(GameEngine& engine) {
    engine.drawTextureToRenderer(sheet->getTexture(), sRect, dRect);
}

void Paddle::mouseMoved(GameEngine& engine, Group* group, SDL_Event* event) {
    int x = event->motion.x;
    int halfW = dRect->w / 2;
    if (x - halfW < 0)
        dRect->x = 0;
    else if (x + halfW > windowW)
        dRect->x = windowW - dRect->w;
    else
        dRect->x = x - halfW / 2;
}
