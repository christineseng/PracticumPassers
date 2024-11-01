// Name        : graphicsTest2.cpp
// Author      : Erick Martinez
// Version     :
// Copyright   : Your copyright notice
// Description : BallHeaderFile

#ifndef BALL_H
#define BALL_H
#include "SDL_Plotter.h"
#include <cmath>

//Class for ball fucntions like creating balls
//and gettting the balls location and size;
class Ball
{
public:
    //BALL-FUNCTIONS
    void drawBall(point loc, SDL_Plotter& win);
    void drawBall(point loc, int size, color c,  SDL_Plotter& win);
    /*void ballFalling(point ballLoc, point clickPos, int velocity, SDL_Plotter& win);*/
    //GETTERS
    int getBallLoc() { return location;}
private:
    int location;
    color c;
};

class Block{
    public:
        void drawSquare(point loc, int length, int width, color c, SDL_Plotter &win);
        void drawTriangle(point topVertex, point leftVertex, point rightVertex, color c, SDL_Plotter &g);
        void drawCircle(point loc, int size, color c, SDL_Plotter &g);
        void drawLine(point loc1, point loc2, color c, SDL_Plotter &g);
        double distance(point loc1, point loc2);

private:
    int location;
    int size;
    
};

#endif //BALL_H
