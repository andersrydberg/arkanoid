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
    void tick(GameEngine& sys, Group* group) override;
    static Explosion* getInstance(int x, int y);

protected:
    Explosion(int x, int y);

private:
    int ticksToLive;
};



class Bullet : public Sprite {

public:
    static Bullet* getInstance(int x, int y);

    void tick(GameEngine& sys, Group *group) override;


private:
    Bullet(int x, int y);

    double xVelocity, yVelocity;
    bool bCollided;
};



class Pistol : public Sprite {

public:
    Pistol() = default;

    void mouseDown(GameEngine& sys, Group* group, SDL_Event* event) override;
};


#endif
