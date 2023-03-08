//
// Created by Anders Rydberg on 2022-12-27.
//

#include "Arkanoid.h"
#include "GameEngine.h"
#include "Constants.h"

using namespace std;

// random device for randomizing brick color
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(0, 6);



//// ArkanoidSpriteSheet

ArkanoidSpriteSheet::ArkanoidSpriteSheet(GameEngine* engine)
: SpriteSheet(engine, constants::gResPath + constants::spriteSheetRelPath) { }


/// Brick

Brick::Brick(ArkanoidSpriteSheet* sheet, int x, int y)
: SpriteFromSheet(sheet, &sheet->blueBrick1, x, y) {
    // randomize color
    sRect->x += distrib(gen) * 54;
}

void Brick::checkCollision(GameEngine* engine, Group* group, Component* other, Group* otherGroup) {
    if (!bCollided)
        if (engine->componentsIntersect(this, other)) {
            counter = 0;
            bCollided = true;
        }
}

void Brick::tick(GameEngine* engine, Group* group) {
    if (bCollided) {
        if (counter == 25)
            group->remove(this);
        else if (counter % 5 == 0)
            sRect->y += 22;
        counter++;
    }
}


//// Paddle

Paddle::Paddle(ArkanoidSpriteSheet* sheet, int x, int y)
: SpriteFromSheet(sheet, &sheet->bluePaddle4, x, y) { }

void Paddle::mouseMoved(GameEngine* engine, Group* group, SDL_Event* event) {
    const int newX = event->motion.x - dRect->w / 2;     // align mouse to the center of the paddle
    const int maxX = 920 - dRect->w;

    if (newX < 104)
        dRect->x = 104;
    else if (newX > maxX)
        dRect->x = maxX;
    else
        dRect->x = newX;

    if (!bBallReleased)
        // send new x-coordinate to the ball (which follows the paddle before being released)
        group->message(to_string(dRect->x), "ball");
}

void Paddle::receiveMessage(Group* group, const string& message) {
    if (message == "released!")
        bBallReleased = true;
}


//// Ball

Ball::Ball(ArkanoidSpriteSheet* sheet, int x, int y)
: SpriteFromSheet(sheet, &sheet->ball0x0, x, y) { }

void Ball::mousePressed(GameEngine* engine, Group* group, SDL_Event* event) {
    if (!bReleased) {
        velocity = 10.0;
        const double initialAngle = PI * 1.75;
        xVel = velocity * cos(initialAngle);
        yVel = velocity * sin(initialAngle);
        bReleased = true;
        group->message("released!", "paddle");
    }
}

void Ball::tick(GameEngine* engine, Group* group) {
    if (bReleased) {
        dRect->x += static_cast<int>(round(xVel));
        dRect->y += static_cast<int>(round(yVel));
    }
}

void Ball::receiveMessage(Group* group, const std::string& message) {
    if (!bReleased)
        dRect->x = stoi(message) + 20;
}

void Ball::checkCollision(GameEngine* engine, Group* group, Component* other, Group* otherGroup) {
    SDL_Rect intersection;
    if (SDL_IntersectRect(dRect, other->getDRect(), &intersection)) {
        if (otherGroup->getName() == "paddle") {
            // check x-position relative to paddle; x*=coefficient; y*=-1
        }
        else if (otherGroup->getName() == "walls") {
            // check wall orientation; y*=-1 or x*=-1
        }
    }
}
