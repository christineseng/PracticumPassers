/*
 * block.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: nolanschirripa
 */

#include "Block.h"

#include "SDL_Plotter.h"

//Constructors
Block::Block(): location(), c(), life(0), shape("") {}
Block::Block(point loc, color col, int l, string s): location(loc), c(col), life(l), shape(s){
	//FIXME depending on the shape, set the hit boxes differently
	HitBox b;
	b.setPoint(loc);
	b.setLength(85);
	b.setWidth(85);
	hb1 = b;
	hb2 = b;
}


//Member Functions
void Block::drawSquare(point loc, int size, color c, SDL_Plotter& win) {
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
/*void Block::drawRandomShape() {
	srand(time(0));
	int randNum;
	randNum = rand() % 11;
	switch (randNum) {
	case 1: {
		drawCircle()
	}
	}

}
*/

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



