/*
* Ball.h
 *
 *  Created on: Nov 1, 2024
 *  Author: nolanschirripa
 */


#ifndef BALL_H
#define BALL_H
#include "SDL_Plotter.h"
#include "HitBox.h"
#include "force.h"
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
    //FORCE-FUNCTIONS
    void setMagnitude(double m){f.setMagnitude(m);}
    void setDirection(double d){f.setDirection(d);}
    double getMagnitude(){return f.getMagnitude();}
    double getDirection(){return f.getDirection();}
    void apply(force newForce){f.apply(newForce);}

    //GETTERS
    point& getBallLoc(){ return location; }
    HitBox& getHitBox(){ return hb; }
    force& getForce(){ return f; }
private:
    point location;
    color c;
    HitBox hb;
    force f;
};



#endif /* BALL_H_ */
 
