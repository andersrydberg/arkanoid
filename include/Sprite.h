//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef SPRITE_H
#define SPRITE_H


#include "Component.h"
#include "Map.h"

class Sprite : public Component {

public:
    Sprite();
    explicit Sprite(const std::string& filepath);
    Sprite(const std::string& filepath, int x, int y, int w, int h);
    ~Sprite();

    void draw();

protected:
    SDL_Rect* rect;
    SDL_Texture* texture;
    Map* map;

};


#endif
