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
    //Block Attributes
    point location;
    int life;
    color blockColor;
    string shape;


    //HitBoxes
    HitBox hb;

    //Level
    int currentLevel = 0;
    int levelOffsetY = 0;//how far a block should move up
    vector<Block> allActiveShapes;


public:
    //Constructors
    Block();
    Block(point loc, string s);

    //setters
   /*
    * description: sets location to point p
    * return: void
    * Pre: valid argument point p
    * Post: location changed to point p
    */
    void setLocation(point p) {
        location.x = p.x;
        location.y = p.y;
    }

   /*
    * description: sets life to l
    * return: void
    * Pre: valid argument int l
    * Post: life changed to point l
    */
    void setLife(int l) {life = l;}

   /*
    * description: sets allActiveShapesLife
    * return: void
    * Pre: valid argument integer arguments
    * Post: vector allActiveShapesLife changed to integer values
    */
    void setAllActiveShapesLife (int, int);

   /*
    * description: sets shape to string s
    * return: void
    * Pre: valid string argument for s
    * Post: shape changed to s
    */
    void setShape(string s) {shape = s;}

   /*
    * description: changes blockColor based on life
    * return: void
    * Pre: none
    * Post: blockColor changed
    */
    void updateBlockColor();


    //getters

   /*
    * description: gets life
    * return: int
    * Pre: none
    * Post: life returned and unchanged
    */
    int getLife() const {return life;}

   /*
    * description: gets location
    * return: point
    * Pre: none
    * Post: location returned and unchanged
    */
    point getLocation() const {return location;}


   /*
    * description: gets blockColor
    * return: color
    * Pre: none
    * Post: blockColor returned and unchanged
    */
    color getColor() const {return blockColor;}

   /*
    * description: gets the shape name
    * return: string
    * Pre: none
    * Post: shape name returned and unchanged
    */
    string getShape() const {return shape;}

   /*
    * description: gets the hit box around a shape
    * return: HitBox
    * Pre: none
    * Post: Hitbox hb returned and unchanged
    */
    HitBox getHitBox() const {return hb;}

   /*
    * description: gets allActiveShapes on canvas
    * return: vector<Block>
    * Pre: none
    * Post: vector allActiveShapes returned
    */
    vector<Block>& getAllActiveShapes() {
        return allActiveShapes;
    }



    //Member functions:

   /*
    * description: decreases block life
    * return: void
    * Pre: none
    * Post: life decreased by 1 if above 0
    */
    void decreaseLife();

   /*
    * description: draws a square of color c on screen at point
    * return: void
    * Pre: valid loc, color, and window
    * Post: square drawn location changed to center of square
    */
    void drawSquare(point loc, int size, color c, SDL_Plotter &win);

   /*
    * description: draws a triangle of color c on screen at point
    * return: void
    * Pre: valid loc, color, and window
    * Post: triangle drawn location changed to center of triangle
    */
    void drawTriangle(point centroid, int size, color c, SDL_Plotter& g);

    void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g);

   /*
    * description: draws a circle of color c on screen at point
    * return: void
    * Pre: valid loc, color, and window
    * Post: circle drawn location changed to center of circle
    */
    void drawCircle(point loc, int size, color c, SDL_Plotter &g);

   /*
    * description: draws a line from two points on screen
    * return: void
    * Pre: valid loc1 and loc2, color, and window
    * Post: line drawn data members unchanged
    */
    void drawLine (point loc1, point loc2, color c, SDL_Plotter &g) const;

   /*
    * description: returns true if a block is hit
    * return: bool
    * Pre: valid HitBox ballHB and window
    * Post: boolean returned data members unchanged
    */
    bool isHit(HitBox ballHB, SDL_Plotter &g){
        return (HitBox::isHit(ballHB, hb));
    }

   /*
    * description: calculates distance between two points
    * return: double
    * Pre: valid points loc1 and loc2
    * Post: distance found and data members unchanged
    */
    double distance (point loc1, point loc2) const;

    //Levels
    void createLevel(point startLoc);
    void drawLevel(point startLoc, SDL_Plotter& g);
    void nextLevel();
    void drawRandomShape(point loc, int size, color c, SDL_Plotter& g, int state);

};


#endif //BLOCK_H
