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
#include "Ball.h"
#include "Block.h"
#include "flag.h"
#include "blockFlag.h"

using namespace std;

int main(int argc, char ** argv)
{
	//Data Abstraction------------DEBUG----------------------------------------


    SDL_Plotter g(1000, 1000);
    point p;
    point clickPos;
    point squarePoint, trianglePoint;
    force f; //ball force
    const force GRAVITY(0.5, 0);
    const force PUSHRIGHT(0.2, M_PI/2);
    const force PUSHLEFT(0.2, 3*M_PI/2);
    Ball shooter;
    Block square;

    p.x = 500;
    p.y = 50;
    squarePoint.x = 500;
    squarePoint.y = 500;
    trianglePoint.x = 500;
    trianglePoint.y = 750;
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
    int xDist;
    int yDist;
    int flagNum;
    double xPos; //keeps track of location as double for better accuracy
    double yPos;
    bool isFalling = false;
    bool hitDetected = false;
    bool firstHit = false;

    Block testSquare(squarePoint, red, 5, "square");

    Flag flag;

    Uint32 RGB;
    shooter.drawBall(p, size, c, g);
    

    while (!g.getQuit()) {
        g.clear();

        //square.drawSquare(squarePoint, 75, red, g);
        testSquare.drawSquare(squarePoint, 75, red, g);
        //square.drawTriangle(trianglePoint, 75, red, g);
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
            f.setMagnitude(13);
            f.setDirection(atan(static_cast<double>(xDist) / yDist));

            c = black;
            isFalling = true;
            firstHit = false;
        }
        
        //when clicked 
        if (isFalling) {
            //apply gravity
            if (firstHit){
                f.apply(GRAVITY);
                //f.setMagnitude(6);
            }
            //change y and x pos based on magnitude and direction
            yPos += f.getMagnitude() * cos(f.getDirection());
            p.y = static_cast<int> (yPos);
            if (p.y < size + 3){
                p.y = size + 3;
            }
            else if (p.y > g.getRow() - size - 3){
                p.y = g.getRow() - size - 3;
            }
            xPos += f.getMagnitude() * sin(f.getDirection());
            p.x = static_cast<int> (xPos);
            if (p.x < size + 3){
                p.x = size + 3;
            }
            else if (p.x > g.getCol() - size - 3){
                p.x = g.getCol() - size - 3;
            }

            //update flag positions
            flag.update(p.x, p.y, size);
            flagNum = flag.isHit(g);
            if (p.y > 980)
            {
                isFalling = false;
                p.y = 50;
                p.x = 500;
            }

            if (flagNum != -1){
                if (!firstHit){
                    firstHit = true;
                }
                f.setMagnitude(f.getMagnitude() - 0.4);
                if (f.getMagnitude() < 0){
                    f.setMagnitude(0);
                    isFalling = false;
                }
            }

            if (flagNum == 0){
                cout << "top flag initial: " << f.getDirection() << endl;
                f.setDirection(M_PI - f.getDirection());
                cout << "top flag new: " << f.getDirection() << endl;
            }
            else if (flagNum == 2){
                cout << "bottom flag: " << f.getDirection() << endl;
                f.setDirection(3 * M_PI - f.getDirection());
                //if direction is close to straight up/down, set it to the closest PI/8 value so that it doesn't get stuck bouncing up/down
                if (f.getDirection() >= 7.0 * M_PI / 8.0 && f.getDirection() <= M_PI){
                    f.setDirection(7.0 * M_PI / 8.0);
                }
                else if (f.getDirection() >=  M_PI && f.getDirection() <= 9.0 * M_PI / 8.0){
                    f.setDirection(9.0 * M_PI / 8.0);
                }
                cout << "bottom flag new: " << f.getDirection() << endl;
            }
            
            else if (flagNum == 1){
                cout << "right flag: " << f.getDirection() << endl;
                f.setDirection(0 - f.getDirection());
                if ((f.getDirection() > 15.0/16.0 * M_PI && f.getDirection() < 17.0/16.0 * M_PI) || (f.getDirection() > 31.0/16.0 * M_PI) || f.getDirection() < 1.0/16.0 * M_PI){
                    f.apply(PUSHLEFT);
                }
                //f.apply(PUSHLEFT);
                cout << "right flag new: " << f.getDirection() << endl;
            }
            else if (flagNum == 3){
                cout << "left flag: " << f.getDirection() << endl;
                f.setDirection(0 - f.getDirection());
                if (f.getDirection() > 15.0/16.0 * M_PI && f.getDirection() < 17.0/16.0 * M_PI || f.getDirection() > 31.0/16.0 || f.getDirection() < 1/16.0 * M_PI){
                    f.apply(PUSHRIGHT);
                }
                //f.apply(PUSHRIGHT);
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


            //check if shapes hit
            if (testSquare.isHit(g)){
                cout << "square hit !!" << endl;
            }
        }
        g.update();
    }
}
	
