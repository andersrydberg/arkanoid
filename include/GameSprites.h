//
// Created by Anders Rydberg on 2022-12-07.
//

#ifndef GAMESPRITES_H
#define GAMESPRITES_H

#include "Sprite.h"
#include "Constants.h"

class Explosion : public Sprite {

public:
    void tick(GameEngine& engine, Group* group) override;
    static Explosion* getInstance(GameEngine& engine, int x, int y);

private:
    Explosion(GameEngine& engine, int x, int y);
    int ticksToLive;
};


class BulletGroup : public Group {

public:
    void tick(GameEngine& engine) override;
    void pause();
    static BulletGroup* getInstance(World* world, const std::string& name);

private:
    BulletGroup(World* world, const std::string& name)
    : Group(world, name), bPaused(false) {}
    bool bPaused;
};


class Bullet : public Sprite {

public:
    void tick(GameEngine& engine, Group *group) override;
    void checkCollision(GameEngine& engine, Group* group, Component* other, Group* otherGroup) override;
    static Bullet* getInstance(GameEngine& engine, int x, int y);

private:
    Bullet(GameEngine& engine, int x, int y);
    int windowW, windowH;
    double internalX, internalY, xVelocity, yVelocity;
    bool bCollided;
};



class Pistol : public Sprite {

public:
    Pistol() = default;

    void mouseDown(GameEngine& engine, Group* group, SDL_Event* event) override;
};


#endif
