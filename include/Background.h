//
// Created by Anders Rydberg on 2022-11-21.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <string>
#include "Component.h"

class Background : public Component {

public:
    explicit Background(std::string filePath);
    void draw() const override;

private:
    SDL_Texture* texture;
};


#endif
