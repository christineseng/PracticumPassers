/*
sudo add-apt-repository ppa:kisak/kisak-mesa
sudo apt update
sudo apt upgrade

export LIBGL_ALWAYS_SOFTWARE=1
*/
#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

void drawCircle(point loc, int size, color c, SDL_Plotter& g);

int main(int argc, char ** argv)
{

    SDL_Plotter g(1000,1000);
    point p(500, 500);
    color c;
    c.R = 0;
    c.G = 0;
    c.B = 0;
    color w;
    w.R = 255;
    w.G = 255;
    w.B = 255;
    int size = 100;
    Uint32 RGB;

    drawCircle(p, size, c, g);
    while (!g.getQuit())
    {
        for(int i =0; i < 500; i+=10)
        {
            p.y = 500 + i;
            drawCircle(p, size, c, g);
            g.update();
            drawCircle(p, size, w, g);
            p.y = 500 + i;
        }
    }
    g.getQuit();
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
