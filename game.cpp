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

using namespace std;

int main(int argc, char ** argv)
{
	//Data Abstraction------------DEBUG----------------------------------------

	//BALL-ATTRIBUTES
	Ball shooter;
	point ballLoc;
	ballLoc.x = 500; ballLoc.y = 50;
	color black, red;
	black.R = 0;   black.B = 0;   black.G = 0;
	red.R = 255;   red.B = 0;     red.G = 0;
	int const size = 10;

	//BLOCK-ATTRIBUTES
	Block sqaure;
	point blockLoc;
	blockLoc.x = 450; blockLoc.y = 950;
	color sc;
	sc.R = 255;
	sc.G = 100;
	sc.B = 120;

	//MAGNITUDE+VELOCITY
	int const velocity = 10;
	force f;
	int xDist, yDist;
	double xPos, yPos; //keeps track of location as double for better accuracy

	//-----------------------------DEBUG^-----------------------------------------

    point clickPos;
	Uint32 RGB;
    SDL_Plotter window(1000, 1000);
	bool isFalling = false;

	//Process--------------------------------
	cout << "BUMPKIN" << endl;
	while (!window.getQuit()) {
		window.clear();

		shooter.drawBall(ballLoc, size, black, window);
		sqaure.drawSquare(blockLoc, 70, 70, red, window);
		//when clicked x and y calculates distance from start to click point
		if (window.mouseClick()) {
			clickPos = window.getMouseClick();
			ballLoc.y = 50;
			ballLoc.x = 500;
			xPos = ballLoc.x;
			yPos = ballLoc.y;
			xDist = clickPos.x - ballLoc.x;
			yDist = clickPos.y - ballLoc.y;
			//sets magnitude based on how far from start you click
			f.setMagnitude(sqrt(pow(xDist, 2) + pow(yDist, 2)) / 60);
			f.setDirection(atan(static_cast<double>(xDist)/yDist));

			shooter.drawBall(ballLoc, size, black, window);
			isFalling = true;
		}

		//when clicked
		if (isFalling) {
			//change y and x pos based on magnitude and direction
			yPos += f.getMagnitude() * cos(f.getDirection());
			ballLoc.y = static_cast<int> (yPos);
			xPos += f.getMagnitude() * sin(f.getDirection());
			ballLoc.x = static_cast<int> (xPos);

			if (ballLoc.x <= 10 || ballLoc.x >= 990 || ballLoc.y <= 10 || ballLoc.y >= 990){
				isFalling = false;
				shooter.drawBall(ballLoc, size, red, window);
			}
		}
    	window.update();//UPDATE WINDOW
    }
	return 0;
}