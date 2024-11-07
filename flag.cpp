#include "flag.h"

Flag::Flag(){
    //x = 0; 
    //y = 0;
    point topArray[5];
    point bottomArray[5];
    point leftArray[5];
    point rightArray[5];
}

void Flag::update(int newX, int newY, int ballSize){
    point p;
    for (int i = 0; i < 5; ++i){
        p.x = newX + (3 * (i - 2));
        p.y = newY - ballSize;
        topArray[i] = p;
        
        p.x = newX + (3 * (i - 2));
        p.y = newY + ballSize;
        bottomArray[i] = p;

        p.x = newX + ballSize;
        p.y = newY + (3 * (i - 2));
        rightArray[i] = p;

        p.x = newX - ballSize;
        p.y = newY + (3 * (i - 2));
        leftArray[i] = p;
    }
}
int Flag::isHit(SDL_Plotter& g){
    int sideNum;
    if (isHit(topArray, g)){
        sideNum = 0;
    }
    else if (isHit(rightArray, g)){
        sideNum = 1;
    }
    else if (isHit(bottomArray, g)){
        sideNum = 2;
    }
    else if (isHit(leftArray, g)){
        sideNum = 3;
    }
    else{//if not hit
        sideNum = -1;
    }
    return sideNum;
}
//checks if row of flags is hit
bool Flag::isHit(point pointArray[], SDL_Plotter& g){
    bool hit = false;
    for (int i = 0; i < 5; ++i){
        if (isHit(pointArray[i], g)){
            hit = true;
        }
    }
    return hit;
}
//checks if point p is hit
bool Flag::isHit(point p, SDL_Plotter& g){
    bool result = false;
    if (g.getColor(p.x, p.y) != flagWhite && g.getColor(p.x, p.y) != flagBlack){
        result = true;
    }
    if (p.x < 5 || p.x > g.getRow() - 5){
        result = true;
    }
    if (p.y < 5 || p.y > g.getCol() - 5){
        result = true;
    }

    return result;
}

/*void Flag::update(int newX, int newY, int ballSize, bool vertical){
    point p;
    if (vertical){
        p.x = newX;
        p.y = newY;
        //pointArray[0] = 
    }
}*/
/*void Flag::update(int newX, int newY){
    x = newX;
    y = newY;
}*/