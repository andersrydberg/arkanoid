#include <iostream>
#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.
#include "System.h"
#include "Session.h"
#include "Background.h"
#include "Sprite.h"

// Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// Bifogas endast för test av SDL installation! 

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>
#include <random>

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

Session ses;

const double distanceTravelledPerTick = 4.0;
std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> dis(0.0, 8 * atan(1));  // 2 * pi

class Bullet : public Sprite {

public:
    static Bullet* getInstance(int x, int y) {
        return new Bullet(x, y);
    }

    ~Bullet() override {
        SDL_DestroyTexture(texture);
    }

    void tick() override {
        rect.x += distanceTravelledPerTick * cos(angle);
        rect.y += distanceTravelledPerTick * sin(angle);

        if (rect.y <= 0 || rect.x <= 0)
            ses.remove(this);
        //rect.y -= 4;
    }

    void draw() const override {
        SDL_RenderCopy(sys.rend, texture, NULL, &rect);
    }

protected:
    Bullet(int x, int y) : Sprite(x, y, 32, 32) {
        SDL_Surface* surface =
                IMG_Load((constants::gResPath + "images/donkey.png").c_str());
        texture = SDL_CreateTextureFromSurface(sys.rend, surface);
        SDL_FreeSurface(surface);
        std::cout << angle << std::endl;
    }

private:
    SDL_Texture* texture;

    double angle = dis(gen);

};



class Pistol : public Sprite {

public:
    Pistol() : Sprite() {
    }

    void mouseDown(SDL_Event* event) override {
        int x = event->button.x;
        int y = event->button.y;
        ses.add(Bullet::getInstance(x, y));
    }
};



int main(int argc, char* argv[]) {
    if (sys.initWithErrors())
        return EXIT_FAILURE;

    SDL_RendererInfo info;
    SDL_GetRendererInfo(sys.rend, &info);
    std::cout << info.name << std::endl;

    Background* bg = Background::getInstance(constants::gResPath + "images/bg.jpg");
    Pistol pistol;

    ses.add(bg);
    ses.add(&pistol);
    ses.run();

	return EXIT_SUCCESS;
}