//
// Created by Anders Rydberg on 2022-11-21.
//

#include "GameEngine.h"
#include "Sprite.h"
#include <SDL2/SDL_image.h>

// has neither texture nor rect
Sprite::Sprite() : rect {nullptr}, texture {nullptr} {
}

// has texture but no rect (fill window)
Sprite::Sprite(GameEngine& engine, const std::string& filepath) : rect {nullptr} {
    texture = engine.getTextureFromImage(filepath);
}

// has texture and rect (typical sprite)
Sprite::Sprite(GameEngine& engine, const std::string& filepath, int x, int y, int w, int h) {
    rect = new SDL_Rect {x, y, w, h};
    texture = engine.getTextureFromImage(filepath);
}


Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
    delete rect;
}


void Sprite::draw(GameEngine& engine) {
    if (texture && bVisible)
        SDL_RenderCopy(engine.getRenderer(), texture, nullptr, rect);
}