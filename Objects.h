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
    point getBallLoc() { return location;}
private:
    point location;
    color c;
};

class Block{
    private:
    point location;
    color c;
    int life;

	public:
		//Constuctors
		Block();
		Block (point loc, color col, int l);

		//setters
		void setLocation(point p) {
			location.x = p.x;
			location.y = p.y;
		}
		void setColor(color c) {this -> c = c;}
		void setLife(int l) {life = l;}

		//getters
		point getLocation() const {return location;}
		color getColor() const {return c;}
		int getLife() const {return life;}

		//Member functions:
		void drawSquare(point loc, int length, int width, color c, SDL_Plotter &win);
        void drawTriangle(point topVertex, point leftVertex, point rightVertex, color c, SDL_Plotter &g);
        void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g);
        void drawCircle(point loc, int size, color c, SDL_Plotter &g);
        void drawLine (point loc1, point loc2, color c, SDL_Plotter &g) const;
        void drawRandomShape();
        bool isHit(SDL_Plotter &g);
        double distance (point loc1, point loc2) const;

};
#endif //BALL_H
