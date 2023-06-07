//
// Created by Anders Rydberg on 2023-01-14.
//

#include "GameEngine.h"
#include "SpriteSheet.h"
#include <SDL2/SDL.h>

SpriteSheet::SpriteSheet(GameEngine *engine, const std::string &filePath)
{
    texture = engine->getTextureFromImage(filePath);
}

SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(texture);
}

SDL_Texture *SpriteSheet::getTexture() const
{
    return texture;
}