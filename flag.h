#ifndef flag_h
#define flag_h

#include "SDL_Plotter.h"

class Flag{
    public:
        Flag();
        void update(int newX, int newY);
        bool isHit(SDL_Plotter& g);

    private:
        int x;
        int y;

};
#endif