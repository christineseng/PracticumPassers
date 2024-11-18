//
// Created by User on 11/13/2024.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "SDL_Plotter.h"
#include "force.h"
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

public:
    //Constuctors
    Block();
    Block(point loc, color col, int l, string s, int st);

    //setters
    void setLocation(point p)
    {
        location.x = p.x;
        location.y = p.y;
    }

    void setColor(color c) { this->c = c; }
    void setLife(int l) { life = l; }
    void setState();

    //getters
    point getLocation() const { return location; }
    color getColor() const { return c; }
    int getLife() const { return life; }

    //Member functions:
    void drawSquare(point loc, int size, color c, SDL_Plotter& win);
    void drawTriangle(point centroid, int size, color c, SDL_Plotter& g);
    void drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter& g);
    void drawCircle(point loc, int size, color c, SDL_Plotter& g);
    void drawBall(point loc, int size, color c, SDL_Plotter& win);
    void drawLine(point loc1, point loc2, color c, SDL_Plotter& g) const;
    double distance(point loc1, point loc2) const;

    //Levels
    void createLevel(point startLoc);
    void drawLevel(point startLoc, SDL_Plotter& g);
    void nextLevel();
    void drawRandomShape(point loc, int size, color c, SDL_Plotter& g, int state);

    //Ball Life
    bool isHit(SDL_Plotter& g);

};


#endif //BLOCK_H
