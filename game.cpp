//============================================================================
// Name        : graphicsTest2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include "force.h"
#include "SDL_Plotter.h"

using namespace std;

void drawCircle(point loc, int size, color c, SDL_Plotter& g);

int main(int argc, char ** argv)
{

    SDL_Plotter g(1000, 1000);
    point p;
    point clickPos;
    force f;


    p.x = 500;
    p.y = 50;
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

    Uint32 RGB;
    drawCircle(p, size, c, g);
    while (!g.getQuit()) {
        g.clear();

        drawCircle(p, size, c, g);
        //when clicked x and y calculates distance from start to click point
        if (g.mouseClick()) {
        	clickPos = g.getMouseClick();
        	p.y = 50;
        	p.x = 500;
        	xPos = p.x;
            yPos = p.y;
        	xDist = clickPos.x - p.x;
        	yDist = clickPos.y - p.y;
            //sets magnitude based on how far from start you click
            f.setMagnitude(sqrt(pow(xDist, 2) + pow(yDist, 2)) / 60);
            f.setDirection(atan(static_cast<double>(xDist)/yDist));

            c = black;
			drawCircle(p, size, c, g);
			isFalling = true;
        }
        
        //when clicked 
        if (isFalling) {
            //change y and x pos based on magnitude and direction
            yPos += f.getMagnitude() * cos(f.getDirection());
            p.y = static_cast<int> (yPos);
            xPos += f.getMagnitude() * sin(f.getDirection());
            p.x = static_cast<int> (xPos);

            if (p.x <= 10 || p.x >= 990 || p.y <= 10 || p.y >= 990){
                isFalling = false;
                c = red;
                drawCircle(p, size, c, g);
            }
        }
        g.update();
    }

}


