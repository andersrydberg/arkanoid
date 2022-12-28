#include "GameEngine.h"
#include "Constants.h"
#include "Arkanoid.h"


int main(int argc, char* argv[]) {
    GameEngine& engine = GameEngine::getInstance("Arkanoid", windowW, windowH);
    if (engine.initWithErrors())
        return EXIT_FAILURE;

    SpriteSheet sheet = SpriteSheet(engine);
    World* world = engine.getWorld();

    auto paddle = new Paddle(&sheet, &sheet.bluePaddle4, 500, 660);
    world->add(paddle, "paddle");
    auto ball = new Ball(&sheet, &sheet.ball1x1, paddle);
    world->add(ball, "ball");

    engine.setFPS(100);
    engine.run();

	return EXIT_SUCCESS;
}