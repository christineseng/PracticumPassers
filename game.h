//
// Created by User on 12/6/2024.
//

#ifndef GAME_H
#define GAME_H


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

    //BALL
    bool isFalling = false;
    bool hitDetected = false;
    bool firstHit = false;
    Ball shooter;
    Flag ballFlags;

    //FRAMERATE
    Timer fpsTimer;
    int countedFrames;
    int frameTicks;

    //LEVELS
    Block shape;
    point startLoc = {500, 850};
    bool levelChanged = true;

    //SCREENS
    bool gameOver = false;
    enum GameState {
        START_SCREEN,
        PLAYING,
        GAME_OVER
    };
    GameState currentState;

public:
    int score = 0;
    static int maxDifficulty;
    static int minDifficulty;

    //constructor
    Game();

    // functions
    //************************************************************
    //  description: runs game
    //  return: void
    //  pre: none
    //  post: game run
    //************************************************************
    void run();
    //************************************************************
    //  description: drop ball
    //  return: void
    //  pre: none
    //  post: ball launched, isFalling set true
    //************************************************************
    void launchBall();
    //************************************************************
    //  description: ball is falling/updating, checking for hits
    //  return: void
    //  pre: none
    //  post: ball is falling
    //************************************************************
    void ballFalling();
    //************************************************************
    //  description: check for ball hits, update direction and blocks if
    //  anything hit, int parameter represents index of Block in array to check
    //  return: void
    //  pre: none
    //  post: if hit play sound, update direction, update score
    //************************************************************
    void checkHits(int);
    //************************************************************
    //  description: reset ball to top, draw the new level, draw all shapes in
    //  new positions
    //  return: void
    //  pre: none
    //  post: update screen for next level
    //************************************************************
    void updateLevel();
    //************************************************************
    //  description: check if ball hit botttom of screen
    //  return: void
    //  pre: ball location initialized
    //  post: ball remains unchanged
    //************************************************************
    bool bottomHit();
    //************************************************************
    //  description: Draws tect to start screen
    //  return: void
    //  pre: sdl window created
    //  post: start screen passed with ' '
    //************************************************************
    void drawStartScreen();
    //************************************************************
    //  description: Draws tect to start screen
    //  return: void
    //  pre: sdl window created
    //  post: start screen passed with ' '
    //************************************************************
    void drawEndScreen();
    //************************************************************
    //  description: Check if game is over
    //  return: bool
    //  pre: sdl window created
    //  post: flag retubred
    //************************************************************
    bool checkGameOver();
    bool getGameOver()const{return gameOver;}
    void setGameOver(bool f){gameOver = f;}
};


#endif //GAME_H
