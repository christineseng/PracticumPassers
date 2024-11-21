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
    Block(point loc, int newLife, string s);

    //setters
    void setLocation(point p) {
        location.x = p.x;
        location.y = p.y;
    }
    void setLife(int l) {life = l;}
    void setShape(string s) {shape = s;}


    //getters
    int getLife() {return life;}
    point getLocation() const {return location;}
    color getColor();
    int getLife() const {return life;}
    string getShape() const {return shape;}
    HitBox getHitBox() const {return hb; }
    vector<Block> getAllActiveShapes() const{return allActiveShapes;}

    //Member functions:
    void decreaseLife();
    void drawSquare(point loc, int size, color c, SDL_Plotter &win);
    void drawTriangle(point centroid, int size, color c, SDL_Plotter& g);
    void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter &g);
    void drawCircle(point loc, int size, color c, SDL_Plotter &g);
    void drawLine (point loc1, point loc2, color c, SDL_Plotter &g) const;
    bool isHit(HitBox ballHB, SDL_Plotter &g){
        return (HitBox::isHit(ballHB, hb));
    }
    double distance (point loc1, point loc2) const;

    //Levels
    void createLevel(point startLoc);
    void drawLevel(point startLoc, SDL_Plotter& g);
    void nextLevel();
    void drawRandomShape(point loc, int size, color c, SDL_Plotter& g, int state);

};


#endif //BLOCK_H
