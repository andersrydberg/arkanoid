#include "GameEngine.h"
#include "SpriteFromSheet.h"
#include "Constants.h"
#include "Arkanoid.h"

/*
 * note: SDL libraries, if needed, are included in GameEngine.h, so need not be
 * included here
 */

int main(int argc, char* argv[]) {

    /*
     * Initialize the game engine. An exception is thrown if SDL cannot be properly
     * initialized.
     */
    GameEngine* engine;
    try {
        engine = GameEngine::initialize("Arkanoid", windowW, windowH);
    }
    catch (sdl_initialization_error&) {
        return 1;
    }

    /*
     * The World object is where all visual components reside. Components are grouped
     * into instances of the 'Group' class. Removing a component or a group using any
     * of the dedicated member functions results in object deletion, so the user must
     * take care not to leave any dangling references to these objects.
     */
    World* world = engine->getWorld();

    /*
     * Implementations of 'SpriteSheet' are not visual components and are not part of
     * the 'World'. They are used when instantiating objects of the 'SpriteFromSheet'
     * class.
     */
    ArkanoidSpriteSheet sheet = ArkanoidSpriteSheet(engine);

    //// populate the world
    /// walls
    Group* walls = world->addGroup("group");
    walls->bCanCollideInternally = false;
    walls->add(new Wall(&sheet, &sheet.silverWallCorner0x0, 86, 0));
    for (int n = 0; n < 12; n++)
        walls->add(new Wall(&sheet, &sheet.vertSilverWall, 86, 20 + n * 56));
    for (int n = 0; n < 14; n++)
        walls->add(new Wall(&sheet, &sheet.horSilverWall, 106 + n * 56, 0));
    walls->add(new Wall(&sheet, &sheet.horSilverWallLeftHalf, 890, 0));
    walls->add(new Wall(&sheet, &sheet.silverWallCorner1x0, 918, 0));
    walls->add(new Wall(&sheet, &sheet.vertSilverWallLowerHalf, 920, 20));
    for (int n = 0; n < 11; n++)
        walls->add(new Wall(&sheet, &sheet.vertSilverWall, 920, 48 + n * 56));
    walls->add(new Wall(&sheet, &sheet.vertSilverWallUpperHalf, 920, 664));

    world->add(new Paddle(&sheet, 500, 660), "paddle");
    world->add(new Ball(&sheet, 520, 644), "ball");

    // engine->setFPS(60);      // 60 is the default frame rate

    SDL_ShowCursor(SDL_DISABLE);
    engine->run();


	return 0;
}