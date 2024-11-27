#include "flag.h"

Flag::Flag(){
    x = 0;
    y = 0;
    point topArray[5];
    point bottomArray[5];
    point leftArray[5];
    point rightArray[5];
    point topRight;
    point bottomRight;
    point bottomLeft;
    point topLeft;
    flagSpace = 3;
}

void Flag::update(int newX, int newY, int ballSize, force& newF){
    //update force
    f = newF;
    point p;
    //update edges
    for (int i = 0; i < 5; ++i){
        p.x = newX + (flagSpace * (i - 2));
        p.y = newY - ballSize - 3;
        topArray[i] = p;

        p.x = newX + (flagSpace * (i - 2));
        p.y = newY + ballSize + 3;
        bottomArray[i] = p;

        p.x = newX + ballSize + 3;
        p.y = newY + (flagSpace * (i - 2));
        rightArray[i] = p;

        p.x = newX - ballSize - 3;
        p.y = newY + (flagSpace * (i - 2));
        leftArray[i] = p;
    }

    //update corners
    //update top right
    p.x = newX + ballSize + 2;
    p.y = newY - ballSize - 2;
    topRight = p;
    //bottom right
    p.x = newX + ballSize + 2;
    p.y = newY + ballSize + 2;
    bottomRight = p;
    //bottom left
    p.x = newX - ballSize - 2;
    p.y = newY + ballSize + 2;
    bottomLeft = p;
    //top left
    p.x = newX - ballSize - 2;
    p.y = newY - ballSize - 2;
    topLeft = p;
}
int Flag::isHit(SDL_Plotter& g){
    int sideNum = -1; //if no sides or corners hit return -1

    if (f.getDirection() >= 0 && f.getDirection() <= M_PI / 2){ //check bottom, right, bottom-right
        if(rowIsHit(bottomArray, 2, g)){
            sideNum = 2;
        }
        else if (rowIsHit(rightArray, 1, g)){
            sideNum = 1;
        }
        else if (cornerIsHit(bottomRight, g)){
            sideNum = 5;
        }
    }
    else if (f.getDirection() >= M_PI / 2 && f.getDirection() <= M_PI){ //check right, top, top-right
        if (rowIsHit(rightArray, 1, g)){
            sideNum = 1;
        }
        else if (rowIsHit(topArray, 0, g)){
            sideNum = 0;
        }
        else if (cornerIsHit(topRight, g)){
            sideNum = 4;
        }
    }
    else if (f.getDirection() >= M_PI && f.getDirection() <= 3 * M_PI / 2){ //check top, left, top-left
        if (rowIsHit(topArray, 0, g)){
            sideNum = 0;
        }
        else if (rowIsHit(leftArray, 3, g)){
            sideNum = 3;
        }
        else if (cornerIsHit(topLeft, g)){
            sideNum = 7;
        }
    }
    else if (f.getDirection() >= 3 * M_PI / 2 && f.getDirection() <= 2 * M_PI){ //check left, bottom, bottom-left
        if (rowIsHit(bottomArray, 2, g)){
            sideNum = 2;
        }
        else if (rowIsHit(leftArray, 3, g)){
            sideNum = 3;
        }
        else if (cornerIsHit(bottomLeft, g)){
            sideNum = 6;
        }
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
    //check if color hit
    if (g.getColor(p.x, p.y) != flagWhite && g.getColor(p.x, p.y) != flagBlack && g.getColor(p.x, p.y) != flagEmpty){
        result = true;
    }

    //check if edge of screen hit
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
    else if (sideNum == 3){ //checking left
        if (p.x < 5){
            result = true;
        }
    }

    return result;
}

bool Flag::cornerIsHit(point p, SDL_Plotter& g){
    bool result = false;
    if (g.getColor(p.x, p.y) != flagWhite && g.getColor(p.x, p.y) != flagBlack && g.getColor(p.x, p.y) != flagEmpty){
        result = true;
    }
    return result;
}

