#ifndef blockflag_h
#define blockflag_h

#include "SDL_Plotter.h"


const int CIRCLEFLAGSLENGTH = 50;
const int TRIANGLEFLAGSLENGTH = 26;
const int SQUAREFLAGSLENGTH = 10;
class BlockFlag{
    private:
        point location;
        string shape;

        point circleFlags[CIRCLEFLAGSLENGTH];

        point triangleSide1Flags[TRIANGLEFLAGSLENGTH];
        point triangleSide2Flags[TRIANGLEFLAGSLENGTH];
        point triangleSide3Flags[TRIANGLEFLAGSLENGTH];
        
        point squareSide1Flags[SQUAREFLAGSLENGTH];
        point squareSide2Flags[SQUAREFLAGSLENGTH];
        point squareSide3Flags[SQUAREFLAGSLENGTH];
        point squareSide4Flags[SQUAREFLAGSLENGTH];
    public:
        BlockFlag();
        BlockFlag(point loc, string s);
        bool isHit(SDL_Plotter& g);
        bool pointIsHit(point p, SDL_Plotter& g);
        void initializeFlags();
        void setLocation(point l){
            location = l;
        }
        void setShape(string s){
            shape = s;
        }

};
#endif