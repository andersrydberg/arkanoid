//
// Created by Anders Rydberg on 2022-12-26.
//

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

class AnimatedSprite : public Sprite
{

public:
    ~AnimatedSprite() override;

    void draw(GameEngine *engine) override;

protected:
    AnimatedSprite();

    std::unordered_map<std::string, SDL_Texture *> textures;
    std::string currentTexture;
};

#endif
