#ifndef newgame_h
#define newgame_h

#include <iostream>
#include <cmath>
#include "force.h"
#include "SDL_Plotter.h"
#include "Ball.h"
#include "Block.h"
#include "flag.h"
#include "HitBox.h"
#include "Timer.h"
#include <vector>



const int SCREEN_FPS = 150;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const color BLACKCOLOR = {0, 0, 0};
const color WHITECOLOR = {255, 255, 255};
const int BALLSIZE = 10;

const force GRAVITY(0.5, 0);
const force PUSHRIGHT(0.5, 3 * M_PI / 2);
const force PUSHLEFT(0.5, 3 * M_PI / 2);

class Game{
private:
	SDL_Plotter g{1000,1000};

    point ballPoint;
    point clickPos;

    int flagNum;

    int xDist;
    int yDist;
    double xPos;
    double yPos;

    bool isFalling = false;
    bool hitDetected = false;
    bool firstHit = false;
    bool gameOver = false;

    //FRAMERATE
    Timer fpsTimer;
    int countedFrames;
    int frameTicks;

    //LEVELS
    Block shape;
    point startLoc = {500, 850};
    bool levelChanged = true;

    //debug
    Ball shooter;
    Flag ballFlags;
public:
    static int score;
    static int maxDifficulty;
    static int minDifficulty;

    //constructor
    Game();

    //functions
    void run();
    void launchBall();
    void ballFalling();
    void updateLevel();
    bool bottomHit();
    void setGameOver();
    void displayGameOverScreen();
};

#endif
