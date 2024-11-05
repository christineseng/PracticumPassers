#include "flag.h"

Flag::Flag(){
    x = 0; 
    y = 0;
}

bool Flag::isHit(SDL_Plotter& g){
    bool result;
    if (g.getColor(x, y) != WHITE){
        result = true;
    }
    result = false;
    //test

    return result;
}
void Flag::update(int newX, int newY){
    x = newX;
    y = newY;
}