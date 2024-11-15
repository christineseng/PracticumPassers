#include "blockFlag.h"

BlockFlag::BlockFlag(){

}
BlockFlag::BlockFlag(point loc, string s){
    location = loc;
    shape = s;
}

void BlockFlag::initializeFlags(){
    point p;
    /*if (shape == "circle"){

    }*/
    if (shape == "square"){
        for (int i = 0; i < SQUAREFLAGSLENGTH; ++i){
            //top array
            p.y = location.y - (75 / 2);
            p.x = location.x - (75 / 2) + (3 * i);
            squareSide1Flags[i] = p;

            //bottom array
            p.y = location.y + (75 / 2);
            p.x = location.x - (75 / 2) + (3 * i);
            squareSide2Flags[i] = p;

            //left array
            p.x = location.x - 1 - (75/2);
            p.y = location.y - (75 / 2) + (3 * i);
            squareSide3Flags[i] = p;

            //right array
            p.x = location.x + 1 + (75 / 2);
            p.y = location.y - (75 / 2) + (3 * i);
            squareSide4Flags[i] = p;
        }
    }
    else if (shape == "triangle"){
        int offset;
        int topVertexY = location.y - (2.0/3.0) * 65;
        for (int i = 0; i < 65; i += 5){
            offset = (i / static_cast<double>(65)) * (75/2.0);
            //left array
            p.x = location.x - offset;
            p.y = topVertexY + i;
            triangleSide1Flags[i] = p;

            //right array
            p.x = location.x + offset;
            p.y = topVertexY + i;
            triangleSide2Flags[i] = p;

            //bottom array
            p.x = location.x - (65 / 2) + i;
            p.y = topVertexY + 65;
            triangleSide3Flags[i] = p;
        }
    }
}

bool BlockFlag::isHit(SDL_Plotter& g){
    bool result = false;
    if (shape == "circle"){
        for (int i = 0; i < CIRCLEFLAGSLENGTH && !result; ++i){
            if (pointIsHit(circleFlags[i], g)){
                result = true;
            }
        }
    }
    else if (shape == "square"){
        for (int i = 0; i < SQUAREFLAGSLENGTH && !result; ++i){
            if (pointIsHit(squareSide1Flags[i], g)){
                result = true;
            }
        }
        for (int i = 0; i < SQUAREFLAGSLENGTH && !result; ++i){
            if (pointIsHit(squareSide2Flags[i], g)){
                result = true;
            }
        }
        for (int i = 0; i < SQUAREFLAGSLENGTH && !result; ++i){
            if (pointIsHit(squareSide3Flags[i], g)){
                result = true;
            }
        }
        for (int i = 0; i < SQUAREFLAGSLENGTH && !result; ++i){
            if (pointIsHit(squareSide4Flags[i], g)){
                result = true;
            }
        }
    }
    else if (shape == "triangle"){
        for (int i = 0; i < TRIANGLEFLAGSLENGTH && !result; ++i){
            if (pointIsHit(triangleSide1Flags[i], g)){
                result = true;
            }
        }
        for (int i = 0; i < TRIANGLEFLAGSLENGTH && !result; ++i){
            if (pointIsHit(triangleSide2Flags[i], g)){
                result = true;
            }
        }
        for (int i = 0; i < TRIANGLEFLAGSLENGTH && !result; ++i){
            if (pointIsHit(triangleSide3Flags[i], g)){
                result = true;
            }
        }
    }

    return result;
}

bool BlockFlag::pointIsHit(point p, SDL_Plotter& g){
    bool result = false;
    if (g.getColor(p.x - 1, p.y - 1) == 0){
        result = true;
    }
    else if (g.getColor(p.x + 1, p.y - 1) == 0){
        result = true;
    }
    else if (g.getColor(p.x - 1, p.y + 1) == 0){
        result = true;
    }
    else if (g.getColor(p.x + 1, p.y + 1) == 0){
        result = true;
    }

    return result;
}