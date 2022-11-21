//
// Created by Anders Rydberg on 2022-11-21.
//

#include <SDL2/SDL_image.h>
#include "Background.h"
#include "System.h"

/**
 * Convenience class for creating background images
 * @param filePath
 */
Background::Background(const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    texture = SDL_CreateTextureFromSurface(sys.rend, surface);
    SDL_FreeSurface(surface);
}

void Background::draw() const {
    SDL_RenderCopy(sys.rend, texture, NULL, NULL);
}

Background *Background::getInstance(const std::string& filePath) {
    return new Background(filePath);
}
