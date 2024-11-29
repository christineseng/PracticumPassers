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
    //************************************************************
    // description: sets location to point p
    // return: void
    // pre: valid argument point p
    // post: location changed to point p
    //************************************************************
    void setLocation(point p) {
        location.x = p.x;
        location.y = p.y;
    }


    //************************************************************
    // description: sets life to l
    // return: void
    // pre: valid argument int l
    // post: life changed to int l
    //************************************************************
    void setLife(int l) {life = l;}

    //************************************************************
    // description: sets allActiveShapesLife
    // return: void
    // pre: valid int arguments
    // post: life of allActiveShapesLife[index] set to l
    //************************************************************
    void setAllActiveShapesLife (int l, int index);

    //************************************************************
    // description: sets shape to string s
    // return: void
    // pre: valid string argument for s
    // post: shape changed to s
    //************************************************************
    void setShape(string s) {shape = s;}

    //************************************************************
    // description: changes blockColor based on life
    // return: void
    // pre: life has been initialized
    // post: blockColor changed
    //************************************************************
    void updateBlockColor();


    //getters

    //************************************************************
    // description: returns life
    // return: int
    // pre: life initialized
    // post: life remains unchanged
    //************************************************************
    int getLife() const {return life;}

    //************************************************************
    // description: gets location
    // return: point
    // pre: location initialized
    // post: location remains unchanged
    //************************************************************
    point getLocation() const {return location;}


    //************************************************************
    // description: gets blockColor
    // return: color
    // pre: blockColor initialized
    // post: blockColor remains unchanged
    //************************************************************
    color getColor() const {return blockColor;}


    //************************************************************
    // description: gets shape string
    // return: string
    // pre: shape string initialized
    // post: shape remains unchanged
    //************************************************************
    string getShape() const {return shape;}

    //************************************************************
    // description: gets hit box
    // return: HitBox
    // pre: hit box initialized
    // post: hit box remains unchanged
    //************************************************************
    HitBox getHitBox() const {return hb;}

    //************************************************************
    // description: gets allActiveShapes on screen
    // return: vector<Block>
    // pre: allActiveShapes initialized
    // post: vector allActiveShapes returned
    //************************************************************
    vector<Block>& getAllActiveShapes() {
        return allActiveShapes;
    }



    //Member functions:

    //************************************************************
    // description: decreases block life
    // return: void
    // pre: life initialized
    // post: life decreased by 1 if above 0
    //************************************************************
    void decreaseLife();

    //************************************************************
    // description: draws a square of color c on screen at point
    // return: void
    // pre: valid loc, color, and window
    // post: square drawn location changed to center of square
    //************************************************************
    void drawSquare(point loc, int size, color c, SDL_Plotter &win);

    //************************************************************
    // description: draws a triangle of color c on screen at point
    // return: void
    // pre: valid loc, color, and window
    // post: triangle drawn location changed to center of triangle
    //************************************************************
    void drawTriangle(point centroid, int size, color c, SDL_Plotter& g);

    void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g);

    //************************************************************
    // description: draws a circle of color c on screen at point
    // return: void
    // pre: valid loc, color, and window
    // post: circle drawn location changed to center of circle

    //************************************************************
    void drawCircle(point loc, int size, color c, SDL_Plotter &g);

    //************************************************************
    // description: draws a line from two points on screen
    // return: void
    // pre: valid loc1 and loc2, color, and window
    // post: line drawn, data members unchanged
    //************************************************************
    void drawLine (point loc1, point loc2, color c, SDL_Plotter &g) const;

    //************************************************************
    // description: returns true if a block is hit
    // return: bool
    // pre: valid HitBox ballHB and window
    // post: boolean returned data members unchanged
    //************************************************************
    bool isHit(HitBox ballHB, SDL_Plotter &g){
        return (HitBox::isHit(ballHB, hb));
    }

    //************************************************************
    // description: calculates distance between two points
    // return: double
    // pre: valid points loc1 and loc2
    // post: distance found and data members unchanged
    //************************************************************
    double distance (point loc1, point loc2) const;

    //Levels
    //************************************************************
    // description: creates a new level with three shapes based on the start location
    // return: void
    // pre: startLoc is centered on the x axis, and valid point on the screen
    // post: three new shapes added to allActiveShapes vector
    //************************************************************
    void createLevel(point startLoc);
    //************************************************************
    // description: draws all shapes
    // return: void
    // pre: startLoc is same point used to create levels
    // post: all shapes drawn onto the screen
    //************************************************************
    void drawLevel(point startLoc, SDL_Plotter& g);
    //************************************************************
    // description: increases current level by one
    // return: void
    // pre: currentLevel is initialized
    // post: currentLevel += 1
    //************************************************************
    void nextLevel();
    //************************************************************
    // description: increases current level by one
    // return: void
    // pre: currentLevel is initialized
    // post: currentLevel += 1
    //************************************************************

};

#endif //BLOCK_H
