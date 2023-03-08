//
// Created by Anders Rydberg on 2022-11-21.
//

#include "GameEngine.h"
#include "Sprite.h"
#include <SDL2/SDL_image.h>

using namespace std;

Sprite::Sprite(GameEngine* engine, const std::string& filepath,
               int x, int y, int w, int h,
               bool visible) {
    if (x == 0 && y == 0 && w == 0 && h == 0)
        rect = nullptr;
    else
        rect = new SDL_Rect {x, y, w, h};
    bVisible = visible;
    texture = engine->getTextureFromImage(filepath);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
    delete rect;
}


// returns a sprite that stretches to fill the entire window
Sprite* Sprite::getInstance(GameEngine* engine, const string& filepath) {
    return new Sprite(engine, filepath);
}

// returns a "typical" sprite with a size and relative position
Sprite* Sprite::getInstance(GameEngine* engine, const string& filepath,
                            int x, int y, int w, int h) {
    return new Sprite(engine, filepath, x, y, w, h);
}

Sprite* Sprite::getInstance(GameEngine* engine, const string& filepath,
                            int x, int y, int w, int h,
                            bool visible) {
    return new Sprite(engine, filepath, x, y, w, h, visible);
}


void Sprite::draw(GameEngine* engine) {
    if (texture && bVisible)
        engine->drawTextureToRenderer(texture, rect);
}
