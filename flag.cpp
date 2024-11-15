#include "flag.h"

Flag::Flag(){
    x = 0; 
    y = 0;
}

bool Flag::isHit(SDL_Plotter& g){
    bool result = false;
    if (g.getColor(x, y) != flagWhite && g.getColor(x, y) != flagBlack){
        result = true;
    }
    if (x < 5 || x > g.getRow() - 5){
        result = true;
    }
    if (y < 5 || y > g.getCol() - 5){
        result = true;
    }

    return result;
}
void Flag::update(int newX, int newY){
    x = newX;
    y = newY;
}