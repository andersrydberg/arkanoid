#include <iostream>
#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.
#include "System.h"
#include "Session.h"
#include "Sprite.h"
#include "GameSprites.h"

// Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// Bifogas endast för test av SDL installation! 

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>

/*  PATH TO YOUR RESOURCE FOLDER 'resources'
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*
*   Change to your own path if you choose a different approach!
*   Absolut Path(Second choice)
*   gResPath = "/Users/kjellna/dev/cpp/sdl2_second/resources/";
*
*   If you need to copy your 'resources' folder into directory
*   '/build/debug/', in that case change gResPath="./resources/"
*/


const int windowW = 1024;
const int windowH = 720;




int main(int argc, char* argv[]) {
    if (sys.initWithErrors())
        return EXIT_FAILURE;

    sys.setWindowTitle("Game");
    sys.setWindowSize(windowW, windowH);

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(sys.rend, &info);
//    std::cout << info.name << std::endl;

    Map* map = ses.getMap();

    map->setBackground(constants::gResPath + "images/bg.jpg");

    Pistol pistol;
    map->add(&pistol);

    ses.run();

	return EXIT_SUCCESS;
}