#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

void drawCircle(point loc, int size, color c, SDL_Plotter& g);

int main(int argc, char ** argv)
{

    SDL_Plotter g(1000,1000);
    point p;
    color c;
    int size;
    Uint32 RGB;

    while (!g.getQuit())
    {

		if(g.kbhit()){
			switch(toupper(g.getKey())){
				case 'C': g.clear();
				          break;
			}
		}

		if(g.mouseClick()){
			p = g.getMouseClick();
			size = rand()%50;
			c.R  = rand()%256;
			c.G  = rand()%256;
			c.B  = rand()%256;
			drawCircle(p, size, c, g);
		}
		g.update();

    }
}
