#include "GameEngine.h"
#include "Arkanoid.h"

/*
 * note: SDL libraries, if needed, are included in GameEngine, so need not be
 * included here
 */

const std::string RESOURCES_PATH = "../resources/";
const std::string SPRITESHEET_REL_PATH =
        "images/arkanoid_breakout_high_definition_spritesheet_by_netroco_ddbkgym.png";


int main(int argc, char *argv[])
{
    GameEngine engine("Arkanoid", WINDOW_W, WINDOW_H);

    if (!engine.isInitialized())
        return 1;


    /*
     * The World object is where all visual components reside. Components are grouped
     * into instances of the 'Group' class. Removing a component or a group using any
     * of the dedicated member functions results in object deletion, so the user must
     * take care not to leave any dangling references to these objects.
     */
    World *world = engine.getWorld();

    /*
     * Implementations of 'SpriteSheet' are not visual components and are not part of
     * the 'World'. They are used when instantiating objects of the 'SpriteFromSheet'
     * class.
     */
    SpriteSheet sheet = SpriteSheet(engine, RESOURCES_PATH + SPRITESHEET_REL_PATH);

    //// populate the world
    /// walls
    Group *walls = world->addGroup("walls");
    walls->setCollideInternally(false);
    walls->add(new Wall(&sheet, silverWallCorner0x0, 86, 0, -1, -1));
    for (int n = 0; n < 12; n++)
        walls->add(new Wall(&sheet, vertSilverWall, 86, 20 + n * 56, -1, 1));
    for (int n = 0; n < 14; n++)
        walls->add(new Wall(&sheet, horSilverWall, 106 + n * 56, 0, 1, -1));
    walls->add(new Wall(&sheet, horSilverWallLeftHalf, 890, 0, 1, -1));
    walls->add(new Wall(&sheet, silverWallCorner1x0, 918, 0, -1, -1));
    walls->add(new Wall(&sheet, vertSilverWallLowerHalf, 920, 20, -1, 1));
    for (int n = 0; n < 11; n++)
        walls->add(new Wall(&sheet, vertSilverWall, 920, 48 + n * 56, -1, 1));
    walls->add(new Wall(&sheet, vertSilverWallUpperHalf, 920, 664, -1, 1));

    /// bricks
    Group *bricks = world->addGroup("bricks");
    bricks->setCollideInternally(false);
    for (int n = 0; n < 13; n++)
        for (int m = 0; m < 10; m++)
            bricks->add(new Brick(&sheet, 161 + n * 54, 100 + m * 22));

    world->add(new Paddle(&sheet, 500, 660), "paddle");
    world->add(new Ball(&sheet, 520, 644), "ball");

    // engine.setFPS(60);      // 60 is the default frame rate

    SDL_SetRelativeMouseMode(SDL_TRUE);
    engine.run();

    return 0;
}