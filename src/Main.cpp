#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.
#include "GameEngine.h"
#include "GameSprites.h"


const int windowW = 1024;
const int windowH = 720;


int main(int argc, char* argv[]) {
    GameEngine& engine = GameEngine::getInstance("Game", windowW, windowH);
    if (engine.initWithErrors())
        return EXIT_FAILURE;

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(sys.rend, &info);
//    std::cout << info.name << std::endl;

    engine.setFPS(100);

    World* world = engine.getWorld();
    world->add(new Sprite(constants::gResPath + "images/bg.jpg"), "background");
    world->add(new Pistol, "pistol");
    world->addGroup("bullets");
    world->addGroup("explosions");

    engine.run();

	return EXIT_SUCCESS;
}