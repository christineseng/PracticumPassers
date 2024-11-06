//============================================================================
// Name        : graphicsTest2.cpp
// Author      : Erick Martinez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include "force.h"
#include "SDL_Plotter.h"
#include "Objects.h"
#include "flag.h"

using namespace std;

int main(int argc, char ** argv)
{
	//Data Abstraction------------DEBUG----------------------------------------


    SDL_Plotter g(1000, 1000);
    point p;
    point clickPos;
    point squarePoint;
    force f;
    Ball shooter;
    Block square;

    p.x = 500;
    p.y = 50;
    squarePoint.x = 500;
    squarePoint.y = 500;
    color c;
    color black;
    black.R = 0;
    black.B = 0;
    black.G = 0;
    color red;
    red.R = 255;
    red.B = 0; 
    red.G = 0;
    int size = 10;
    int velocity = 10;
    int xDist;
    int yDist;
    double xPos; //keeps track of location as double for better accuracy
    double yPos;
    bool isFalling = false;
    bool hitDetected = false;

    Flag topFlag;
    Flag bottomFlag;
    Flag rightFlag;
    Flag leftFlag;

    Uint32 RGB;
    shooter.drawBall(p, size, c, g);
    //sets flags' initial position
    topFlag.update(p.x, p.y - size/2);
    bottomFlag.update(p.x, p.y + size/2);
    rightFlag.update(p.x + size/2, p.y);
    leftFlag.update(p.x - size/2, p.y);
    

    while (!g.getQuit()) {
        g.clear();

        square.drawSquare(squarePoint, 25, 25, red, g);
        shooter.drawBall(p, size, c, g);
        //when clicked x and y calculates distance from start to click point
        if (g.mouseClick()) {
        	clickPos = g.getMouseClick();
        	p.y = 50;
        	p.x = 500;
        	xPos = p.x;
            yPos = p.y;
            xDist = clickPos.x - p.x;
        	yDist = clickPos.y - p.y;
            // sets magnitude based on how far from start you click
            f.setMagnitude(sqrt(pow(xDist, 2) + pow(yDist, 2)) / 60);
            f.setDirection(atan(static_cast<double>(xDist) / yDist));

            c = black;
            isFalling = true;
        }
        
        //when clicked 
        if (isFalling) {
            //change y and x pos based on magnitude and direction
            yPos += f.getMagnitude() * cos(f.getDirection());
            p.y = static_cast<int> (yPos);
            xPos += f.getMagnitude() * sin(f.getDirection());
            p.x = static_cast<int> (xPos);

            //update flag positions
            topFlag.update(p.x, p.y - size/2);
            bottomFlag.update(p.x, p.y + size/2);
            rightFlag.update(p.x + size/2, p.y);
            leftFlag.update(p.x - size/2, p.y);
            
            if (topFlag.isHit(g) || bottomFlag.isHit(g)){
                f.setDirection(M_PI - f.getDirection());
            }
            if (rightFlag.isHit(g) || leftFlag.isHit(g)){
                f.setDirection(-f.getDirection());
            }
        }
        g.update();
    }
}
	