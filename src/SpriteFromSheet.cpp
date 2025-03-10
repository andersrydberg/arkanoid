//
// Created by Anders Rydberg on 2023-01-14.
//

#include "SpriteFromSheet.h"

SpriteFromSheet::SpriteFromSheet(SpriteSheet *sheet, const SDL_Rect &sourceRect, int x, int y)
    : SpriteFromSheet(sheet, sourceRect, x, y, sourceRect.w, sourceRect.h) {}

SpriteFromSheet::SpriteFromSheet(SpriteSheet *sheet, const SDL_Rect &sourceRect, int x, int y, int w, int h)
    : sheet(sheet)
{
    sRect = SDL_Rect(sourceRect);
    dRect = SDL_Rect{x, y, w, h};
}


void SpriteFromSheet::draw(GameEngine *engine)
{
    engine->drawTextureToRenderer(sheet->getTexture(), &sRect, &dRect);
}
