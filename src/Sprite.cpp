//
// Created by Anders Rydberg on 2022-11-21.
//

#include "System.h"
#include "Sprite.h"
#include "Session.h"
#include <SDL2/SDL_image.h>

// has neither texture nor rect
Sprite::Sprite() : rect {nullptr}, texture {nullptr} {
    map = ses.getMap();
}

// has texture but no rect (fill window)
Sprite::Sprite(const std::string& filepath) : rect {nullptr} {
    map = ses.getMap();

    SDL_Surface* surface = IMG_Load(filepath.c_str());
    texture = SDL_CreateTextureFromSurface(sys.rend, surface);
    SDL_FreeSurface(surface);
}

// has texture and rect (typical sprite)
Sprite::Sprite(const std::string& filepath, int x, int y, int w, int h) {
    map = ses.getMap();

    rect = new SDL_Rect {x, y, w, h};

    SDL_Surface* surface = IMG_Load(filepath.c_str());
    texture = SDL_CreateTextureFromSurface(sys.rend, surface);
    SDL_FreeSurface(surface);
}


Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
    delete rect;
}


void Sprite::draw() {
    if (!texture)
        return;
    SDL_RenderCopy(sys.rend, texture, nullptr, rect);
}
