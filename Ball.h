/*
 * Ball.h
 *
 *  Created on: Nov 1, 2024
 *      Author: nolanschirripa
 */


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

    //GETTERS
    int getBallLoc() { return location;}
private:
    int location;
    color c;
};



#endif /* BALL_H_ */
