//============================================================================
// Name        : graphicsTest2.cpp
// Author      : Erick Martinez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include "force.h"
#include "SDL_Plotter.h"
#include "Objects.h"
#include "flag.h"

using namespace std;

int main(int argc, char ** argv)
{
	//Data Abstraction------------DEBUG----------------------------------------


    SDL_Plotter g(1000, 1000);
    point p;
    point clickPos;
    point squarePoint;
    point triangleTop(300, 300);
    point triangleLeft(450, 350);
    point triangleRight(750, 750);
    force f; //ball force
    const force GRAVITY(0.5, 0);
    Ball shooter;
    Block square;

    p.x = 500;
    p.y = 50;
    squarePoint.x = 500;
    squarePoint.y = 500;
    color c;
    color black;
    black.R = 0;
    black.B = 0;
    black.G = 0;
    color red;
    red.R = 255;
    red.B = 0; 
    red.G = 0;
    int size = 10;
    int velocity = 10;
    int xDist;
    int yDist;
    int flagNum;
    double xPos; //keeps track of location as double for better accuracy
    double yPos;
    bool isFalling = false;
    bool hitDetected = false;

    Flag flag;

    Uint32 RGB;
    shooter.drawBall(p, size, c, g);
    

    while (!g.getQuit()) {
        g.clear();

        square.drawSquare(squarePoint, 75, 75, red, g);
        square.drawTriangle(triangleTop, triangleLeft, triangleRight, red, g);
        shooter.drawBall(p, size, c, g);
        //when clicked x and y calculates distance from start to click point
        if (g.mouseClick()) {
        	clickPos = g.getMouseClick();
        	p.y = 50;
        	p.x = 500;
        	xPos = p.x;
            yPos = p.y;
            xDist = clickPos.x - p.x;
        	yDist = clickPos.y - p.y;
            // sets magnitude based on how far from start you click
            // f.setMagnitude(sqrt(pow(xDist, 2) + pow(yDist, 2)) / 60);
            f.setMagnitude(6);
            f.setDirection(atan(static_cast<double>(xDist) / yDist));

            c = black;
            isFalling = true;
        }
        
        //when clicked 
        if (isFalling) {
            //apply gravity
            f.apply(GRAVITY);
            //change y and x pos based on magnitude and direction
            yPos += f.getMagnitude() * cos(f.getDirection());
            p.y = static_cast<int> (yPos);
            if (p.y < size){
                p.y = size;
            }
            else if (p.y > g.getRow() - size){
                p.y = g.getRow() - size;
            }
            xPos += f.getMagnitude() * sin(f.getDirection());
            p.x = static_cast<int> (xPos);
            if (p.x < size){
                p.x = size;
            }
            else if (p.x > g.getCol() - size){
                p.x = g.getCol() - size;
            }

            //update flag positions
            flag.update(p.x, p.y, size);
            flagNum = flag.isHit(g);

            /*if (flagNum != -1){
                f.setMagnitude(f.getMagnitude() - 1);
            }*/

            if (flagNum == 0){
                cout << "top flag initial: " << f.getDirection() << endl;
                f.setDirection(M_PI - f.getDirection());
                cout << "top flag new: " << f.getDirection() << endl;
            }
            else if (flagNum == 2){
                cout << "bottom flag: " << f.getDirection() << endl;
                f.setDirection(3 * M_PI - f.getDirection());
                cout << "bottom flag new: " << f.getDirection() << endl;
            }
            
            else if (flagNum == 1){
                cout << "right flag: " << f.getDirection() << endl;
                f.setDirection(0 - f.getDirection());
                cout << "right flag new: " << f.getDirection() << endl;
            }
            else if (flagNum == 3){
                cout << "left flag: " << f.getDirection() << endl;
                f.setDirection(0 - f.getDirection());
                cout << "left flag new: " << f.getDirection() << endl;
            }

            else if (flagNum == 4){ //top right corner hit
                cout << "TOP RIGHT CORNER" << endl;
                f.setDirection(f.getDirection() - M_PI);
            }
            else if (flagNum == 5){ //bottom right corner hit
                cout << "BOTTOM RIGHT CORNER" << endl;
                f.setDirection(M_PI + f.getDirection());
            }
            else if (flagNum == 6){ //bottom left corner hit
                cout << "BOTTOM LEFT CORNER" << endl;
                f.setDirection(M_PI + f.getDirection());
            }
            else if (flagNum == 7){ //top left corner hit
                cout << "TOP LEFT CORNER" << endl;
                f.setDirection(f.getDirection() - M_PI);
            }
        }
        g.update();
    }
}
	