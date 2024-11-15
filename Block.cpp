/*
 * block.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: nolanschirripa
 */

#include "Block.h"

#include "SDL_Plotter.h"

//Constructors
Block::Block(): location(), c(), life(0), shape(""), state(-1) {}
Block::Block(point loc, color col, int l, string s, int st): location(loc), c(col), life(l), shape(s), state(st){}

//Setters
void Block::setState() {
	int randNum;
	randNum = rand() % 10;
	if (state == -1) {
		if (randNum >= 0 && randNum <= 3) { //circle
			state = 1;
		}
		else if (randNum <= 6) { //square
			state = 2;
		}
		else {
			state = 3; //triangle
		}
	}


}

//Member Functions
void Block::drawCircle(point loc, int size, color c, SDL_Plotter &g) {
	shape = "circle";
	location.x = loc.x;
	location.y = loc.y;
	for (double i = -size; i <= size; i += 0.1)
	   {
	       for (double j = -size; j <= size; j += 0.1)
	       {
	           if (i * i + j * j <= size * size)
	           {
	               g.plotPixel(round(loc.x + i), round(loc.y + j), c);
	           }
	       }
	   }
}

void Block::drawSquare(point loc, int size, color c, SDL_Plotter& win) {
	shape = "square";
	location.x = loc.x;
	location.y = loc.y;
	int length, width;
	length = size, width = size;
	// Calculate the top-left corner of the square based on the center
	int startX = loc.x - length / 2;
	int startY = loc.y - width / 2;

	// Draw the square starting from the calculated top-left corner
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			win.plotPixel(startX + i, startY + j, c.R, c.G, c.B);
		}
	}
}

void Block::drawLine (point loc1, point loc2, color c, SDL_Plotter& g) const {
	int changeInX = loc2.x - loc1.x;
	int changeInY = loc2.y - loc1.y;

	int steps;

	if (changeInX >= changeInY) {
		steps = changeInX;
	} else {
		steps = changeInY;
	}

	double xIncrease = changeInX / static_cast<double>(steps);
	double yIncrease = changeInY / static_cast<double>(steps);

	double x;
	double y;
	x = loc1.x;
	y = loc1.y;

	for (int i = 0; i <= steps; ++i) {
		g.plotPixel(round(x),round(y), c);
		x += xIncrease;
		y += yIncrease;

	}
}

double Block::distance(point loc1, point loc2) const{
	double distance;
	distance = sqrt(pow(loc1.x - loc2.x, 2.0) + pow(loc1.y - loc2.y, 2.0));
	return distance;
}

void Block::drawTriangle(point centroid, int size, color c, SDL_Plotter& g) {
	shape = "triangle";
	location.x = centroid.x;
	location.y = centroid.y;

	double height;
	point topVertex, leftVertex, rightVertex;
	point start, end;

	height = (sqrt(3.0) / 2.0) * size;
	topVertex.x = centroid.x;
	topVertex.y = centroid.y - (2.0 / 3.0) * height;

	leftVertex.x = centroid.x - (size / 2.0);
	leftVertex.y = centroid.y + (1.0 / 3.0) * height;

	rightVertex.x = centroid.x + (size / 2.0);
	rightVertex.y = centroid.y + (1.0 / 3.0) * height;

	for (int y = 0; y <= height; ++y) {
		int offset = (y / static_cast<double>(height)) * (size / 2.0);

		// start and end points of the line to draw at this row
		start.x = topVertex.x - offset;
		start.y = topVertex.y + y;

		end.x = topVertex.x + offset;
		end.y = topVertex.y + y;

		// Draw the line for this row
		drawLine(start, end, c, g);
	}
}

void Block::drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g) {
	int sideLength;
	int height;
	int offset; //distance from center to edges
	point start;
	point end;

	sideLength = distance(leftVertex, rightVertex);
	height = (sqrt(3.0) / 2.0) * sideLength;

	for (int y = 0; y <= height; ++y) {
		offset = ((height - y) /static_cast<double>(height)) * (sideLength / 2.0);
		start.x = bottomVertex.x - offset;
		start.y = bottomVertex.y + y;
		end.x = bottomVertex.x + offset;
		end.y = bottomVertex.y + y;
		drawLine(start, end, c, g);
	}
}
void Block::drawRandomShape(point loc, int size, color c, SDL_Plotter& g) {

	setState();
	switch (state) {
	case 1: {
		drawCircle(loc, size - 90, c, g);
		break;
	}
	case 2: {
		drawSquare(loc, size - 40, c, g);
		break;
	}
	case 3: {
		drawTriangle(loc, size, c, g);
		break;
	}
	}

}


/*bool Block::isHit(SDL_Plotter &g) {

	return true;



}
*/
/*
 * void Block::drawTriangle(point topVertex, point leftVertex, point rightVertex, color c, SDL_Plotter& g) {

	location.x = topVertex.x;
	location.y = topVertex.y;

	int sideLength;
	int height;
	int offset; //distance from center to edges
	point start;
	point end;

	sideLength = distance(topVertex, leftVertex);
	height = (sqrt(3.0) / 2.0) * sideLength;

	for (int y = 0; y <= height; ++y) {
		offset = (y /static_cast<double>(height)) * (sideLength / 2.0);
		start.x = topVertex.x - offset;
		start.y = topVertex.y + y;
		end.x = topVertex.x + offset;
		end.y = topVertex.y + y;
		drawLine(start, end, c, g);
	}
}
 */
