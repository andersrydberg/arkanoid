#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.
#include "System.h"
#include "Session.h"
#include "GameSprites.h"


const int windowW = 1024;
const int windowH = 720;




int main(int argc, char* argv[]) {
    System& sys = System::getInstance("Game", windowW, windowH);
    if (sys.initWithErrors())
        return EXIT_FAILURE;

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(sys.rend, &info);
//    std::cout << info.name << std::endl;

    Session& ses = Session::getInstance(sys);
    ses.setFPS(100);

    World* world = ses.getWorld();
    world->add(new Sprite(constants::gResPath + "images/bg.jpg"), "background");
    world->add(new Pistol, "pistol");
    world->addGroup("bullets");
    world->addGroup("explosions");

    ses.run();

	return EXIT_SUCCESS;
}