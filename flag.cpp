#include "flag.h"

Flag::Flag(){
    x = 0; 
    y = 0;
}

bool Flag::isHit(SDL_Plotter& g){
    bool result = false;
    /*if (g.getColor(x, y) != WHITE && g.getColor(x, y) != BLACK){
        result = true;
        cout << "color" << endl;
        if (g.getColor(x, y) != WHITE){
            cout << "not white" << endl;
        }
        if (g.getColor(x, y) != BLACK){
            cout << "not black" << endl;
        }
    }*/
    if (x < 20 || x > g.getRow() - 20){
        result = true;
        cout << "x edge" << endl;
    }
    if (y < 20 || y > g.getCol() - 20){
        result = true;
        cout << "y edge" << endl;
    }

    return result;
}
void Flag::update(int newX, int newY){
    x = newX;
    y = newY;
}