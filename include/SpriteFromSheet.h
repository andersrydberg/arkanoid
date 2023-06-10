//
// Created by Anders Rydberg on 2023-01-14.
//

#ifndef SPRITEFROMSHEET_H
#define SPRITEFROMSHEET_H

#include <SDL2/SDL.h>
#include "Component.h"
#include "SpriteSheet.h"

class SpriteFromSheet : public Component
{
public:
    SpriteFromSheet(SpriteSheet *sheet, const SDL_Rect *sourceRect, int x, int y);
    SpriteFromSheet(SpriteSheet *sheet, const SDL_Rect *sourceRect, int x, int y, int w, int h);
    ~SpriteFromSheet() override;
    void draw(GameEngine *engine) override;

    SDL_Rect *getDRect() override { return dRect; }

protected:
    SpriteSheet *getSheet() { return sheet; }
    SDL_Rect *getSRect() { return sRect; }

private:
    SpriteSheet *sheet;
    SDL_Rect *sRect;
    SDL_Rect *dRect;
};

#endif