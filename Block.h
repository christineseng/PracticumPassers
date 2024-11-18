//
// Created by User on 11/13/2024.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "SDL_Plotter.h"
#include "HitBox.h"
#include <cmath>

class Block
{
private:
    point location;
    color c;
    int life;
    string shape;
    int state;
    vector<int> shapeStates; // keep state of random Shapes
    int currentLevel;
	  HitBox hb1;
	  HitBox hb2;

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
		HitBox getHitBox1() const {return hb1; }
		HitBox getHitBox2() const {return hb2;}

		//Member functions:
		void drawSquare(point loc, int size, color c, SDL_Plotter &win);
		void drawTriangle(point centroid, int size, color c, SDL_Plotter& g);
    void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g);
    void drawCircle(point loc, int size, color c, SDL_Plotter &g);
    void drawLine (point loc1, point loc2, color c, SDL_Plotter &g) const;
    void drawRandomShape();
    bool isHit(HitBox ballHB, SDL_Plotter &g){
		//FIXME add is hit with hit boxes
			  return (HitBox::isHit(ballHB, hb1)) || (HitBox::isHit(ballHB, hb2));
		}
    double distance (point loc1, point loc2) const;
  
    //Levels
    void createLevel(point startLoc);
    void drawLevel(point startLoc, SDL_Plotter& g);
    void nextLevel();
    void drawRandomShape(point loc, int size, color c, SDL_Plotter& g, int state);

};


#endif //BLOCK_H
