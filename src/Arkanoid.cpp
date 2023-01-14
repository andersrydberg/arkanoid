//
// Created by Anders Rydberg on 2022-12-27.
//

#include "Arkanoid.h"
#include "GameEngine.h"
#include "Constants.h"

using namespace std;

//// ArkanoidSpriteSheet

ArkanoidSpriteSheet::ArkanoidSpriteSheet(GameEngine* engine)
: SpriteSheet(engine, constants::gResPath + constants::spriteSheetRelPath) { }



//// Paddle

Paddle::Paddle(ArkanoidSpriteSheet* sheet, int x, int y)
: SpriteFromSheet(sheet, &sheet->bluePaddle4, x, y) { }

void Paddle::mouseMoved(GameEngine* engine, Group* group, SDL_Event* event) {
    int newX = event->motion.x - dRect->w / 2;     // align mouse to the center of the paddle
    int maxX = 920 - dRect->w;

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
        double initialAngle = PI * 1.75;
        xVel = velocity * cos(initialAngle);
        yVel = velocity * sin(initialAngle);
        bReleased = true;
        group->message("released!", "paddle");
    }
}

void Ball::tick(GameEngine* engine, Group* group) {
    if (bReleased) {
        dRect->x += static_cast<int>(std::round(xVel));
        dRect->y += static_cast<int>(std::round(yVel));
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
