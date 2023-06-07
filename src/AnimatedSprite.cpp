//
// Created by Anders Rydberg on 2022-12-26.
//

#include "AnimatedSprite.h"
#include "GameEngine.h"

AnimatedSprite::~AnimatedSprite()
{
    for (const auto &pair : textures)
        SDL_DestroyTexture(pair.second);
}

void AnimatedSprite::draw(GameEngine *engine)
{
    engine->drawTextureToRenderer(textures.at(currentTexture), rect);
}
