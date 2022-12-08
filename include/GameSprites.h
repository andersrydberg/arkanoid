//
// Created by Anders Rydberg on 2022-12-07.
//

#ifndef GAMESPRITES_H
#define GAMESPRITES_H

#include <unordered_set>
#include "Sprite.h"
#include "Constants.h"

class Explosion : public Sprite {

public:
    void tick() override;
    static Explosion* getInstance(int x, int y);

protected:
    Explosion(int x, int y);

private:
    int ticksToLive;
};



class Bullet : public Sprite {

public:
    static Bullet* getInstance(int x, int y);

    void tick() override;


private:
    Bullet(int x, int y);

    double xVelocity, yVelocity;
    bool collided;

    inline static std::unordered_set<Bullet*> bullets;
};



class Pistol : public Sprite {

public:
    Pistol() = default;

    void mouseDown(SDL_Event* event) override;
};


#endif
