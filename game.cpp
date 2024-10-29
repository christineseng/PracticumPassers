#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

void drawCircle(point loc, int size, color c, SDL_Plotter& g);

int main(int argc, char ** argv)
{

    SDL_Plotter g(1000,1000); //open canvas size 1000x1000
    point p(500, 500); //location for center of circle
    color black; //black
    black.R = 0;
    black.G = 0;
    black.B = 0;
    color white; //white
    white.R = 255;
    white.G = 255;
    white.B = 255;
    int size = 100; //size of the circle
    Uint32 RGB;

    while (!g.getQuit()){ //while game has not ended
        for(int i =0; i < 500; i+=10)
        {
            p.y = 500 + i;
            drawCircle(p, size, black, g); //draw black circle
            g.update(); //update screen
            drawCircle(p, size, white, g); //draw white circle
            p.y = 500 + i;
        }
    }
    g.getQuit();
    return 0;
}


void drawCircle(point loc, int size, color c, SDL_Plotter& g){
    for(double i = -size; i <= size;i+=0.1){
        for(double j = -size; j <= size; j+=0.1){
            if(i*i + j*j <= size*size){
                g.plotPixel(round(loc.x+i),round(loc.y+j),c);
            }
        }
    }

}
