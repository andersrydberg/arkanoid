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

const int BRICK_PIXEL_WIDTH = 54;
const int BRICK_PIXEL_HEIGHT = 22;

//// ArkanoidSpriteSheet

ArkanoidSpriteSheet::ArkanoidSpriteSheet(GameEngine *engine)
    : SpriteSheet(engine, constants::gResPath + constants::spriteSheetRelPath) {}

/// Brick

Brick::Brick(ArkanoidSpriteSheet *sheet, int x, int y)
    : SpriteFromSheet(sheet, &sheet->blueBrick1, x, y)
{
    // randomize color by moving the source rectangle a random amount of steps to the right
    getSRect()->x += distrib(gen) * BRICK_PIXEL_WIDTH;
}

void Brick::checkCollision(GameEngine *engine, Group *group, Component *other, Group *otherGroup)
{
    if (!bCollided && engine->componentsIntersect(this, other))
    {
        counter = 0;
        bCollided = true;
    }
}

void Brick::tick(GameEngine *engine, Group *group)
{
    if (bCollided)
    {
        if (counter < 25)
        {
            if (counter % 5 == 0)
                getSRect()->y += BRICK_PIXEL_HEIGHT;
            counter++;
        }
        else
            group->remove(this);
    }
}

//// Paddle

Paddle::Paddle(ArkanoidSpriteSheet *sheet, int x, int y)
    : SpriteFromSheet(sheet, &sheet->bluePaddle4, x, y) {}

void Paddle::mouseMoved(GameEngine *engine, Group *group, SDL_Event *event)
{
    const int newX = event->motion.x - getDRect()->w / 2; // align mouse to the center of the paddle
    const int maxX = 920 - getDRect()->w;

    if (newX < 104)
        getDRect()->x = 104;
    else if (newX > maxX)
        getDRect()->x = maxX;
    else
        getDRect()->x = newX;

    if (!bBallReleased)
        // send new x-coordinate to the ball (which follows the paddle before being released)
        group->message(to_string(getDRect()->x), "ball");
}

void Paddle::receiveMessage(Group *group, const string &message)
{
    if (message == "released!")
        bBallReleased = true;
}

//// Ball

Ball::Ball(ArkanoidSpriteSheet *sheet, int x, int y)
    : SpriteFromSheet(sheet, &sheet->ball0x0, x, y) {}

void Ball::mousePressed(GameEngine *engine, Group *group, SDL_Event *event)
{
    if (!bReleased)
    {
        velocity = 8.0;
        const double initialAngle = PI * 1.75;
        xVel = velocity * cos(initialAngle);
        yVel = velocity * sin(initialAngle);
        bReleased = true;
        group->message("released!", "paddle");
    }
}

void Ball::tick(GameEngine *engine, Group *group)
{
    bCollided = false;
    if (bReleased)
    {
        getDRect()->x += static_cast<int>(round(xVel));
        getDRect()->y += static_cast<int>(round(yVel));
    }
}

void Ball::receiveMessage(Group *group, const std::string &message)
{
    if (!bReleased)
        getDRect()->x = stoi(message) + 20;
}

void Ball::checkCollision(GameEngine *engine, Group *group, Component *other, Group *otherGroup)
{
    if (bCollided)
        return; // do not collide with more than one component per tick
    if (engine->componentsIntersect(this, other))
    {
        bCollided = true;
        if (otherGroup->getName() == "paddle")
        {
            yVel *= -1;
        }
        else if (otherGroup->getName() == "walls")
        {
            Wall *wall = dynamic_cast<Wall *>(other);
            xVel *= wall->x_factor;
            yVel *= wall->y_factor;
        }
        else if (otherGroup->getName() == "bricks")
        {
            SDL_Rect *intersection = engine->getIntersection(this, other);
            if (intersection->w > intersection->h)
                yVel *= -1;
            else
                xVel *= -1;
        }
    }
}

//// Wall

Wall::Wall(ArkanoidSpriteSheet *sheet, const SDL_Rect *sourceRect, int x, int y, int x_factor, int y_factor)
    : SpriteFromSheet(sheet, sourceRect, x, y), x_factor(x_factor), y_factor(y_factor)
{
}
