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
    ~Sprite() override;
    static Sprite* getInstance(GameEngine* engine, const std::string& filepath);
    static Sprite* getInstance(GameEngine* engine, const std::string& filepath, int x, int y, int w, int h);
    static Sprite* getInstance(GameEngine* engine, const std::string& filepath, int x, int y, int w, int h,
                               bool visible);

    void draw(GameEngine* engine) override;

    SDL_Rect* getDRect() override {return rect;}

    bool bVisible;

protected:
    Sprite(GameEngine* engine, const std::string& filepath, int x=0, int y=0, int w=0, int h=0,
           bool visible=true);

    SDL_Rect* rect;
    SDL_Texture* texture;
};


#endif
