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
    void draw() const override;
    static Background* getInstance(const std::string& filePath);

protected:
    explicit Background(const std::string& filePath);

private:
    SDL_Texture* texture;
};


#endif
