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
        void update(int newX, int newY, force& newF);
        void update(int newX, int newY, int ballSize, force& newF);
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
        bool cornerIsHit(point p, SDL_Plotter& g);
        bool pointIsHit(point p, int sideNum, SDL_Plotter& g);
        bool rowIsHit(point pointArray[], int sideNum, SDL_Plotter& g);

};
#endif
