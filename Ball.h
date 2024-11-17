/*
 * Ball.h
 *
 *  Created on: Nov 1, 2024
 *      Author: nolanschirripa
 */


#ifndef BALL_H
#define BALL_H
#include "SDL_Plotter.h"
#include "HitBox.h"
#include <cmath>

//Class for ball fucntions like creating balls
//and gettting the balls location and size;
class Ball
{
public:
    //CONSTRUCTORS
    Ball();
    Ball(point loc, color col):location(loc), c(col){
        HitBox h;
        h.setLength(20);
        h.setWidth(20);
        h.setPoint(loc);
        hb = h;
    }
    //BALL-FUNCTIONS
    void drawBall(point loc, SDL_Plotter& win);
    void drawBall(point loc, int size, color c,  SDL_Plotter& win);

    //GETTERS
    point getBallLoc() { return location;}
    HitBox getHitBox(){ return hb; }
private:
    point location;
    color c;
    HitBox hb;
};



#endif /* BALL_H_ */
