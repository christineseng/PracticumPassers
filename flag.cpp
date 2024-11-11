#include "flag.h"

Flag::Flag(){
    //x = 0; 
    //y = 0;
    point topArray[5];
    point bottomArray[5];
    point leftArray[5];
    point rightArray[5];
    flagSpace = 4;
}

void Flag::update(int newX, int newY, int ballSize){
    point p;
    for (int i = 0; i < 5; ++i){
        p.x = newX + (flagSpace * (i - 2));
        p.y = newY - ballSize;
        topArray[i] = p;
        
        p.x = newX + (flagSpace * (i - 2));
        p.y = newY + ballSize;
        bottomArray[i] = p;

        p.x = newX + ballSize;
        p.y = newY + (flagSpace * (i - 2));
        rightArray[i] = p;

        p.x = newX - ballSize;
        p.y = newY + (flagSpace * (i - 2));
        leftArray[i] = p;
    }
}
int Flag::isHit(SDL_Plotter& g){
    int sideNum;
    if (rowIsHit(topArray, 0, g)){
        sideNum = 0;
    }
    else if (rowIsHit(rightArray, 1, g)){
        sideNum = 1;
    }
    else if (rowIsHit(bottomArray, 2, g)){
        sideNum = 2;
    }
    else if (rowIsHit(leftArray, 3, g)){
        sideNum = 3;
    }
    else{//if not hit
        sideNum = -1;
    }
    return sideNum;
}
//checks if row of flags is hit
bool Flag::rowIsHit(point pointArray[], int sideNum, SDL_Plotter& g){
    bool hit = false;
    for (int i = 0; i < 5; ++i){
        if (pointIsHit(pointArray[i], sideNum, g)){
            hit = true;
        }
    }
    return hit;
}
//checks if point p is hit
bool Flag::pointIsHit(point p, int sideNum, SDL_Plotter& g){
    bool result = false;
    if (g.getColor(p.x, p.y) != flagWhite && g.getColor(p.x, p.y) != flagBlack){
        result = true;
    }
    if (sideNum == 0){ //checking top
        if (p.y < 5){
            result = true;
        }
    }
    else if (sideNum == 1){ //checking right
        if (p.x > g.getCol() - 5){
            result = true;
        }
    }
    else if (sideNum == 2){ //checking bottom
        if (p.y > g.getRow() - 5){
            result = true;
        }
    }
    else{ //checking left
        if (p.x < 5){
            result = true;
        }
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