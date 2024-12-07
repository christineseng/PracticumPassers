/*
* Author: Nolan Schirripa, Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas
* Assignment Title:  Group Project (flag.h)
* Assignment Description: declares flag class that can detect if ball has hit something
* Due Date: 12/09/2024
* Date Created: 10/25/2024
* Date Last Modified: 12/07/2024
*/
#ifndef flag_h
#define flag_h

#include "SDL_Plotter.h"
#include "force.h"

const long flagEmpty = 4294967295;
const long flagWhite = 16777215;
const int flagBlack = 0;

class Flag{
    public:
        Flag();

        //************************************************************
        // description: sets the flags to be centered around the point passed
        // return: void
        // pre: x and y represent valid point on the screen
        // post: flags centered around (newX, newY)
        //************************************************************
        void update(int newX, int newY, force& newF);
        //************************************************************
        // description: sets the flags to be centered around the point passed
        // return: void
        // pre: x and y represent valid point on the screen
        // post: flags centered around (newX, newY)
        //************************************************************
        void update(int newX, int newY, int ballSize, force& newF);
        //************************************************************
        // description: returns an int depending on whether or not flags are 
        // hit; -1 for no hit, 0-3 for sides, 4-7 for corners
        // return: int
        // pre: int x and y are initialized, represent valid point on screen
        // post: flag remains unchanged
        //************************************************************
        int isHit(SDL_Plotter& g);

    private:
        int x;
        int y;
        int flagSpace;
        force f;
        point pointArray[5];
        point topArray[5];
        point bottomArray[5];
        point rightArray[5];
        point leftArray[5];
        point topRight;
        point bottomRight;
        point bottomLeft;
        point topLeft;
        
        //************************************************************
        // description: returns true if the given row is hit
        // return: bool
        // pre: 
        // post: screen remains unchanged
        //************************************************************
        bool rowIsHit(point pointArray[], SDL_Plotter& g);
        //************************************************************
        // description: returns true/false depending on if point is hit
        // return: bool
        // pre: point represents valid point on screen
        // post: screen remains unchanged
        //************************************************************
        bool pointIsHit(point p, SDL_Plotter& g);

};
#endif
