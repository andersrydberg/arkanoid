//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include "Component.h"

class Sprite : public Component {

public:
    Sprite();
    explicit Sprite(const std::string& filepath);
    Sprite(const std::string& filepath, int x, int y, int w, int h);
    ~Sprite() override;

    void draw() override;

    bool bCanCollide {true};
    bool bVisible {true};

protected:
    SDL_Rect* rect;
    SDL_Texture* texture;

private:
};


#endif
