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
#include <unordered_set>

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

const double distanceTravelledPerTick = 5.0;
const double PI = 4 * atan(1);
std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> dis(0.0, 2 * PI);
const int windowW = 1024;
const int windowH = 720;



class Explosion : public Sprite {

public:
    void tick() override {
        if (ticksToLive-- == 0) {
            ses.remove(this);
        }
    }

    void draw() const override {
        SDL_RenderCopy(sys.rend, texture, NULL, &rect);
    }

    static Explosion* getInstance(int x, int y) {
        return new Explosion(x, y);
    }

    ~Explosion() override {
        SDL_DestroyTexture(texture);
    }


protected:
    Explosion(int x, int y) : Sprite(x, y, 40, 40) {
        SDL_Surface* surface =
                IMG_Load((constants::gResPath + "images/explosion.png").c_str());
        texture = SDL_CreateTextureFromSurface(sys.rend, surface);
        SDL_FreeSurface(surface);

        ticksToLive = 10;
    }

private:
    SDL_Texture* texture;
    int ticksToLive;
};



class Bullet : public Sprite {

public:
    static Bullet* getInstance(int x, int y) {
        return new Bullet(x, y);
    }

    ~Bullet() override {
        SDL_DestroyTexture(texture);
    }

    void tick() override {
        // if another bullet has already collided with this bullet, do nothing
        if (collided) {
            return;
        }

        auto new_rect = SDL_Rect{static_cast<int>(rect.x + xVelocity),
                                     static_cast<int>(rect.y + yVelocity),
                                     rect.w, rect.h};
        //double nx = rect.x + xVelocity;
        //double ny = rect.y + yVelocity;

        // detect collisions
        SDL_Rect intersection;
        for (Bullet* b : bullets) {
            if (b == this || b->collided)
                continue;

            if(SDL_IntersectRect(&new_rect, &b->rect, &intersection)) {
                ses.add(Explosion::getInstance(intersection.x + (intersection.w / 2),
                                               intersection.y + (intersection.h / 2)));
                collided = true;
                b->collided = true;
                ses.remove(this);
                ses.remove(b);
                bullets.erase(this);
                bullets.erase(b);
                return;
            }
        }

        // handle bounce
        if (new_rect.x < 0 || new_rect.x + rect.w > windowW) {
            xVelocity *= -1;
        } else if (new_rect.y < 0 || new_rect.y + rect.h > windowH) {
            yVelocity *= -1;
        } else {
            rect = new_rect;
            //rect.x = nx;
            //rect.y = ny;
        }

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

        double angle = dis(gen);
        xVelocity = distanceTravelledPerTick * cos(angle);
        yVelocity = distanceTravelledPerTick * sin(angle);
        collided = false;
        bullets.insert(this);
    }

private:
    SDL_Texture* texture;

    double xVelocity, yVelocity;
    bool collided;

    inline static std::unordered_set<Bullet*> bullets;

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

    sys.setWindowTitle("Game");
    sys.setWindowSize(windowW, windowH);

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(sys.rend, &info);
//    std::cout << info.name << std::endl;

    Background* bg = Background::getInstance(constants::gResPath + "images/bg.jpg");
    Pistol pistol;


    ses.add(bg);
    ses.add(&pistol);
    ses.run();

	return EXIT_SUCCESS;
}