/*
 * block.h
 *
 *  Created on: Nov 1, 2024
 *      Author: nolanschirripa
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "SDL_Plotter.h"
#include <cmath>
#include <ctime>


class Block{
	private:
    point location;
    color c;
    int life;
    string shape;

	public:
		//Constructors
		Block();
		Block (point loc, color col, int l, string s);

		//setters
		void setLocation(point p) {
			location.x = p.x;
			location.y = p.y;
		}
		void setColor(color c) {this -> c = c;}
		void setLife(int l) {life = l;}
		void setShape(string s) {shape = s;}


		//getters
		point getLocation() const {return location;}
		color getColor() const {return c;}
		int getLife() const {return life;}
		string getShape() const {return shape;}

		//Member functions:
		void drawSquare(point loc, int size, color c, SDL_Plotter &win);
		void drawTriangle(point centroid, int size, color c, SDL_Plotter& g);
        void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g);
        void drawCircle(point loc, int size, color c, SDL_Plotter &g);
        void drawLine (point loc1, point loc2, color c, SDL_Plotter &g) const;
        void drawRandomShape();
        //bool isHit(SDL_Plotter &g);
        double distance (point loc1, point loc2) const;

};



#endif /* BLOCK_H_ */
