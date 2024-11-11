#ifndef flag_h
#define flag_h

#include "SDL_Plotter.h"

const long flagWhite = 4294967295;
const int flagBlack = 0;

class Flag{
    public:
        Flag();
        void update(int newX, int newY);
        void update(int newX, int newY, int ballSize);
        int isHit(SDL_Plotter& g);

    private:
        int x;
        int y;
        int flagSpace;
        point pointArray[5];
        point topArray[5];
        point bottomArray[5];
        point rightArray[5];
        point leftArray[5];
        bool pointIsHit(point p, SDL_Plotter& g);
        bool rowIsHit(point pointArray[], SDL_Plotter& g);

};
#endif