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

    Flag flag;

    Uint32 RGB;
    shooter.drawBall(p, size, c, g);

    while (!g.getQuit()) {
        g.clear();

        square.drawSquare(squarePoint, 75, 75, red, g);
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
            flag.update(xPos, yPos, size);

            if (flag.isHit(g) == 0){
                cout << "top flag initial: " << f.getDirection() << endl;
                f.setDirection(M_PI - f.getDirection());
                cout << "top flag new: " << f.getDirection() << endl;
            }
            else if (flag.isHit(g) == 2){
                cout << "bottom flag: " << f.getDirection() << endl;
                f.setDirection(M_PI - f.getDirection());
                cout << "bottom flag new: " << f.getDirection() << endl;
            }
            
            if (flag.isHit(g) == 1){
                cout << "right flag: " << f.getDirection() << endl;
                f.setDirection(-f.getDirection());
                cout << "right flag new: " << f.getDirection() << endl;
            }
            else if (flag.isHit(g) == 3){
                cout << "left flag: " << f.getDirection() << endl;
                f.setDirection(-f.getDirection());
                cout << "left flag new: " << f.getDirection() << endl;
            }
        }
        g.update();
    }
}
	