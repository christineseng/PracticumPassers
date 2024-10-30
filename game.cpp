//============================================================================
// Name        : graphicsTest2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

void drawCircle(point loc, int size, color c, SDL_Plotter& g);

int main(int argc, char ** argv)
{

    SDL_Plotter g(1000, 1000);
    point p;
    point clickPos;


    p.x = 500;
    p.y = 50;
    color c;
    c.R = 0;
    c.B = 0;
    c.G = 0;
    int size = 10;
    int velocity = 10;
    int xDist;
    int yDist;
    double xPos; //keeps track of location as double for better accuracy
    //double yPos;
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
        	xDist = fabs(clickPos.x - p.x);
        	yDist = fabs(clickPos.y - p.y);
			drawCircle(p, size, c, g);
			isFalling = true;
        }
        
        //when clicked 
        if (isFalling) {
        	p.y += velocity;
        	if (clickPos.x > 500) {
        		xPos += 10 * (xDist / static_cast<double>(yDist));
        		p.x = static_cast<int>(xPos);
        	} else if (clickPos.x == 500) {
        		p.x += 0;
        	}
        	else {
        		xPos -= 10 * (xDist / static_cast<double>(yDist));
        		p.x = static_cast<int>(xPos);
        	}

        }
        g.update();
    }

}


void drawCircle(point loc, int size, color c, SDL_Plotter& g){
	for(double i = -size; i <= size;i+=0.1){
		for(double j = -size; j <= size; j+=0.1){
			if(i*i + j*j <= size*size){
				g.plotPixel(round(loc.x+i),round(loc.y+j),c);
			}
		}
	}

}
