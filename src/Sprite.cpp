//
// Created by Anders Rydberg on 2022-11-21.
//

#include "GameEngine.h"
#include "Sprite.h"
#include <SDL_image.h>


Sprite::Sprite(GameEngine *engine, const std::string &filepath,
               int x, int y, int w, int h,
               bool visible) {
    rect = SDL_Rect{x, y, w, h};
    bVisible = visible;
    texture = engine->getTextureFromImage(filepath);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

// returns a sprite that stretches to fill the entire window
Sprite *Sprite::getInstance(GameEngine *engine, const std::string &filepath)
{
    return new Sprite(engine, filepath);
}

// returns a "typical" sprite with a size and relative position
Sprite *Sprite::getInstance(GameEngine *engine, const std::string &filepath,
                            int x, int y, int w, int h)
{
    return new Sprite(engine, filepath, x, y, w, h);
}

Sprite *Sprite::getInstance(GameEngine *engine, const std::string &filepath,
                            int x, int y, int w, int h,
                            bool visible)
{
    return new Sprite(engine, filepath, x, y, w, h, visible);
}

void Sprite::draw(GameEngine *engine)
{
    if (texture && bVisible)
        engine->drawTextureToRenderer(texture, &rect);
}

void Sprite::setVisible(bool value)
{
    bVisible = value;
}
