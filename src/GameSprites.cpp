//
// Created by Anders Rydberg on 2022-12-07.
//

#include "GameSprites.h"
#include "GameEngine.h"
#include "Session.h"
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



void Explosion::tick(GameEngine& sys, Group* group) {
    if (ticksToLive-- == 0)
        group->remove(this);
}

Explosion* Explosion::getInstance(int x, int y) {
    return new Explosion(x, y);
}


Explosion::Explosion(int x, int y) : Sprite(constants::gResPath + "images/explosion.png",
                                     x, y, 40, 40), ticksToLive{10} {}


Bullet* Bullet::getInstance(int x, int y) {
    return new Bullet(x, y);
}

void Bullet::tick(GameEngine& sys, Group *group) {
    // if another bullet has already bCollided with this bullet, do nothing
    if (bCollided)
        return;

    auto new_rect = SDL_Rect{static_cast<int>(rect->x + xVelocity),
                             static_cast<int>(rect->y + yVelocity),
                             rect->w, rect->h};

    // detect collisions
    SDL_Rect intersection;
    for (Component* comp: group->getContents()) {
        if (Bullet* b = dynamic_cast<Bullet*>(comp)) {
            if (b == this || b->bCollided)
                continue;

            if (SDL_IntersectRect(&new_rect, b->rect, &intersection)) {
                Explosion* explosion = Explosion::getInstance(intersection.x + (intersection.w / 2),intersection.y + (intersection.h / 2));
                group->add(explosion,"explosions");

                bCollided = true;
                b->bCollided = true;
                group->remove(this);
                group->remove(b);
                return;
            }
        }
    }

    // handle bounce
    int windowW = sys.getWindowWidth();
    int windowH = sys.getWindowHeight();
    if (new_rect.x < 0 || new_rect.x + rect->w > windowW) {
        xVelocity *= -1;
    } else if (new_rect.y < 0 || new_rect.y + rect->h > windowH) {
        yVelocity *= -1;
    } else {
        *rect = new_rect;
    }

}


Bullet::Bullet(int x, int y) : Sprite(constants::gResPath + "images/donkey.png",
                              x, y, 32, 32) {
    double angle = dis(gen);
    xVelocity = distanceTravelledPerTick * cos(angle);
    yVelocity = distanceTravelledPerTick * sin(angle);
    bCollided = false;
}




void Pistol::mouseDown(GameEngine& sys, Group* group, SDL_Event* event) {
    int x = event->button.x;
    int y = event->button.y;
    group->add(Bullet::getInstance(x, y), "bullets");
}

