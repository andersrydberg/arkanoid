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

    bool canCollide() const {return bCanCollide;}
    bool isVisible() const {return bVisible;}

    void setCanCollide(bool value) {bCanCollide = value;}
    void setVisible(bool value) {bVisible = value;}

protected:
    SDL_Rect* rect;
    SDL_Texture* texture;

private:
    bool bCanCollide {true};
    bool bVisible {true};
};


#endif
