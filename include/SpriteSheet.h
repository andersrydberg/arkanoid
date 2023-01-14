//
// Created by Anders Rydberg on 2023-01-14.
//

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "GameEngine.h"
#include <SDL2/SDL.h>

class SpriteSheet {
public:
    SpriteSheet(GameEngine* engine, const std::string& filePath);
    ~SpriteSheet();

    SDL_Texture* getTexture() const;

private:
    SDL_Texture* texture;
};


#endif
