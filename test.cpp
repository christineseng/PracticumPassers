/*
sudo add-apt-repository ppa:kisak/kisak-mesa
sudo apt update
sudo apt upgrade

export LIBGL_ALWAYS_SOFTWARE=1
*/
#include <iostream>

#include "SDL_Plotter.h"

using namespace std;

int main(int argc, char ** argv)
{
	//test

    SDL_Plotter g(1000,1000);
    int x,y; 
    int red, green, blue;


    while (!g.getQuit()){

    	g.update();

    	if(g.kbhit()){
    	    g.getKey();
    	}

    }
}
