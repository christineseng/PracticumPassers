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

	//-----------------------------DEBUG^-----------------------------------------

    point clickPos;
	Uint32 RGB;
    SDL_Plotter window(1000, 1000);

	//Process--------------------------------
	cout << "BUMPKIN" << endl;
	while (!window.getQuit()) {
		window.clear();

		shooter.drawBall(ballLoc, size, black, window);
		sqaure.drawSquare(blockLoc, 70, 70, red, window);

		if (window.mouseClick()) {
			clickPos = window.getMouseClick();
			shooter.ballFalling(clickPos,window);
		}
    	window.update();//UPDATE WINDOW
    }
	return 0;
}