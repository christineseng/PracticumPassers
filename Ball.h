/*
* Author: Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas, Nolan Schirripa
* Assignment Title:  Group Project (Ball.h)
* Assignment Description: declares ball class that can bounce off blocks and walls
* Due Date: 12/09/2024
* Date Created: 10/25/2024
* Date Last Modified: 12/07/2024
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
    Ball(){
        HitBox h;
        h.setLength(20);
        h.setWidth(20);
        hb = h;
    }
    Ball(point loc, color col):location(loc), c(col){
        HitBox h;
        h.setLength(20);
        h.setWidth(20);
        h.setPoint(loc);
        hb = h;
    }

    //BALL-FUNCTIONS
    //************************************************************
    // description: draws ball at a given point in given color
    // return: void
    // pre: loc is a valid point on the screen
    // post: draws ball at given location
    //************************************************************
    void drawBall(point loc, int size, color c,  SDL_Plotter& win);
    //FORCE-FUNCTIONS
    //************************************************************
    // description: sets magnitude to double parameter
    // return: void
    // pre: m is a valid double
    // post: ball's force's magnitude is m
    //************************************************************
    void setMagnitude(double m){f.setMagnitude(m);}
    //************************************************************
    // description: sets direction to double parameter
    // return: void
    // pre: d is a valid double
    // post: ball's force's direction is m
    //************************************************************
    void setDirection(double d){f.setDirection(d);}
    //************************************************************
    // description: returns magnitude of ball's force
    // return: double representing magnitude
    // pre: magnitude is initialized
    // post: ball's force remains unchanged
    //************************************************************
    double getMagnitude()const {return f.getMagnitude();}
    //************************************************************
    // description: returns direction of ball's force
    // return: double representing direction
    // pre: direction is initialized
    // post: ball's force remains unchanged
    //************************************************************
    double getDirection()const {return f.getDirection();}
    //************************************************************
    // description: applies force parameter to current force
    // return: void
    // pre: ball's force is initialized
    // post: ball's force is the combination of current force and parameter
    //************************************************************
    void apply(force newForce){f.apply(newForce);}

    //SETTERS
    //************************************************************
    // description: sets ball location to point parameter
    // return: void
    // pre: ball's force is initialized
    // post: ball's force is the combination of current force and parameter
    //************************************************************
    void setBallLoc(point& p){
        location = p;
        hb.setPoint(p);
    }

    //GETTERS
    //************************************************************
    // description: returns pointer for ball's location point
    // return: Point reference
    // pre: ball's location is initialized
    // post: ball remains unchanged
    //************************************************************
    point& getBallLoc() { return location; }
    //************************************************************
    // description: returns pointer for ball's hit box
    // return: HitBox reference
    // pre: ball's hit box is initialized
    // post: ball remains unchanged
    //************************************************************
    HitBox& getHitBox() { return hb; }
    //************************************************************
    // description: returns pointer for ball's force
    // return: force reference
    // pre: ball's force is initialized
    // post: ball remains unchanged
    //************************************************************
    force& getForce() { return f; }
private:
    point location;
    color c;
    HitBox hb;
    force f;
};



#endif /* BALL_H_ */
 
