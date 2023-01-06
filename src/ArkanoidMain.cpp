#include "GameEngine.h"
#include "Constants.h"
#include "Arkanoid.h"


int main(int argc, char* argv[]) {
    GameEngine* engine;
    try {
        engine = GameEngine::initialize("Arkanoid", windowW, windowH);
    }
    catch (sdl_initialization_error&) {
        return 1;
    }

    SpriteSheet sheet = SpriteSheet(engine);
        World* world = engine->getWorld();

        /// walls
        Group* walls = world->addGroup("group");
        walls->bCanCollideInternally = false;
        walls->add(new SpriteFromSheet(&sheet, &sheet.silverWallCorner0x0, 86, 0));
        for (int n = 0; n < 12; n++)
            walls->add(new SpriteFromSheet(&sheet, &sheet.vertSilverWall, 86, 20 + n * 56));
        for (int n = 0; n < 14; n++)
            walls->add(new SpriteFromSheet(&sheet, &sheet.horSilverWall, 106 + n * 56, 0));
        walls->add(new SpriteFromSheet(&sheet, &sheet.horSilverWallLeftHalf, 890, 0));
        walls->add(new SpriteFromSheet(&sheet, &sheet.silverWallCorner1x0, 918, 0));
        walls->add(new SpriteFromSheet(&sheet, &sheet.vertSilverWallLowerHalf, 920, 20));
        for (int n = 0; n < 11; n++)
            walls->add(new SpriteFromSheet(&sheet, &sheet.vertSilverWall, 920, 48 + n * 56));
        walls->add(new SpriteFromSheet(&sheet, &sheet.vertSilverWallUpperHalf, 920, 664));


        auto paddle = new Paddle(&sheet, &sheet.bluePaddle4, 500, 660);
        world->add(paddle, "paddle");
        auto ball = new Ball(&sheet, &sheet.ball0x0, paddle);
        world->add(ball, "ball");

        engine->setFPS(60);
        SDL_ShowCursor(SDL_DISABLE);
        engine->run();


	return 0;
}