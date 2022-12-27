//
// Created by Anders Rydberg on 2022-12-26.
//

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

using namespace std;

class AnimatedSprite : public Sprite {

public:
    ~AnimatedSprite() override;

    void draw(GameEngine& engine) override;

protected:
    AnimatedSprite();

    unordered_map<string, SDL_Texture*> textures;
    string currentTexture;
};


#endif
