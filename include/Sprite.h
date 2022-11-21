//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SPRITE_H
#define SPRITE_H


#include "Component.h"

class Sprite : public Component {

public:
    void draw() const {};

protected:
    Sprite();
    Sprite(int x, int y, int w, int h);
    SDL_Rect rect;
};


#endif
