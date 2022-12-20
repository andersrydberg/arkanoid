#include <iostream>
#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.
#include "GameEngine.h"
#include "GameSprites.h"


const int windowW = 1024;
const int windowH = 720;


void pauseBullets(World* world, SDL_Event* event) {
    Group* group = world->getGroup("bullets");
    if (auto bulletGroup = dynamic_cast<BulletGroup*>(group))
        bulletGroup->pause();
}


int main(int argc, char* argv[]) {
    GameEngine& engine = GameEngine::getInstance("Game", windowW, windowH);
    if (engine.initWithErrors())
        return EXIT_FAILURE;

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(engine.rend, &info);
//    std::cout << info.name << std::endl;

    engine.setFPS(100);

    World* world = engine.getWorld();
    world->add(new Sprite(engine, constants::gResPath + "images/bg.jpg"), "background");
    world->add(new Pistol, "pistol");
    world->addGroup(BulletGroup::getInstance(world, "bullets"));
    world->addGroup("explosions");
    engine.addShortcut("P", pauseBullets);

    engine.run();

	return EXIT_SUCCESS;
}