//
// Created by Anders Rydberg on 2022-12-07.
//

#include "GameSprites.h"
#include "GameEngine.h"
#include <SDL2/SDL_image.h>
#include <random>
#include <unordered_set>
#include "Constants.h"
#include "Group.h"

const double distanceTravelledPerTick = 5.0;
const double PI = 4 * atan(1);
std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> dis(0.0, 2 * PI);



Explosion::Explosion(GameEngine& engine, int x, int y)
        : Sprite(engine, constants::gResPath + "images/explosion.png",
                 x, y, 40, 40), ticksToLive {10} {
}

Explosion* Explosion::getInstance(GameEngine& engine, int x, int y) {
    return new Explosion(engine, x, y);
}


void Explosion::tick(GameEngine& engine, Group* group) {
    if (ticksToLive-- == 0)
        group->remove(this);
}


void BulletGroup::tick(GameEngine& engine) {
    if (!bPaused)
        Group::tick(engine);
}

void BulletGroup::pause() {
    bPaused = !bPaused;
}

BulletGroup* BulletGroup::getInstance(World* world, const std::string& name) {
    return new BulletGroup(world, name);
}



Bullet::Bullet(GameEngine& engine, int x, int y)
        : Sprite(engine, constants::gResPath + "images/donkey.png",
                 x, y, 32, 32) {
    double angle = dis(gen);
    internalX = x;
    internalY = y;
    xVelocity = distanceTravelledPerTick * cos(angle);
    yVelocity = distanceTravelledPerTick * sin(angle);
    bCollided = false;
    windowW = engine.getWindowWidth();
    windowH = engine.getWindowHeight();
}

Bullet* Bullet::getInstance(GameEngine& engine, int x, int y) {
    return new Bullet(engine, x, y);
}


void Bullet::tick(GameEngine& engine, Group *group) {
    // if another bullet has already bCollided with this bullet, do nothing
    if (bCollided)
        return;

    double newX = internalX + xVelocity;
    double newY = internalY + yVelocity;
    auto new_rect = SDL_Rect{static_cast<int>(std::round(newX)),
                             static_cast<int>(std::round(newY)),
                             rect->w, rect->h};

    // handle bounce
    if (new_rect.x < 0 || new_rect.x + rect->w > windowW) {
        xVelocity *= -1;
    } else if (new_rect.y < 0 || new_rect.y + rect->h > windowH) {
        yVelocity *= -1;
    } else {
        internalX = newX;
        internalY = newY;
        *rect = new_rect;
    }

}

void Bullet::checkCollision(GameEngine& engine, Group* group, Component* other, Group* otherGroup) {
    if (Bullet* b = dynamic_cast<Bullet*>(other)) {
        if (b->bCollided)
            return;

        SDL_Rect intersection;
        if (SDL_IntersectRect(rect, b->rect, &intersection)) {
            Explosion* explosion = Explosion::getInstance(engine, intersection.x + (intersection.w / 2),
                                                          intersection.y + (intersection.h / 2));
            group->add(explosion,"explosions");

            bCollided = true;
            b->bCollided = true;
            group->remove(this);
            group->remove(b);
        }
    }
}



void Pistol::mouseDown(GameEngine& engine, Group* group, SDL_Event* event) {
    int x = event->button.x;
    int y = event->button.y;
    group->add(Bullet::getInstance(engine, x, y), "bullets");
}

