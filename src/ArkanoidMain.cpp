#include "GameEngine.h"
#include "Constants.h"
#include "Arkanoid.h"


int main(int argc, char* argv[]) {
    GameEngine& engine = GameEngine::getInstance("Arkanoid", windowW, windowH);
    if (engine.initWithErrors())
        return EXIT_FAILURE;

    SpriteSheet sheet = SpriteSheet(engine);
    World* world = engine.getWorld();

    auto paddle = new Paddle(&sheet, &sheet.bluePaddle4, 500, 660, sheet.bluePaddle4.w, sheet.bluePaddle4.h);
    world->add(paddle, "paddle");

    engine.setFPS(100);
    engine.run();

	return EXIT_SUCCESS;
}