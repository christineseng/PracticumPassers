//============================================================================
// Name        : graphicsTest2.cpp
// Author      :
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
#include "HitBox.h"
#include "Timer.h"
#include <vector>

using namespace std;

const int SCREEN_FPS = 150;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char ** argv)
{
	//Data Abstraction------------DEBUG----------------------------------------


    SDL_Plotter g(1000, 1000);
    point p;
    point clickPos;
    point squarePoint, trianglePoint;
    const force GRAVITY(0.5, 0);
    const force PUSHRIGHT(0.5, M_PI/2);
    const force PUSHLEFT(0.5, 3*M_PI/2);

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

    //FRAMERATE
    Timer fpsTimer;
    int countedFrames;
    int frameTicks;

    //LEVELS
    Block shape;
    point startLoc;
    startLoc.x = 500, startLoc.y = 850;
    bool levelChanged = true;
    color test = {255,0,0};
    vector<Block> allBlocks;

    //debug
    Ball shooter(p, black);
    //Block testSquare(squarePoint, red, 5, "square");
    bool bottomHit = false;

    Flag flag;

    Uint32 RGB;
    shooter.drawBall(p, size, c, g);


    while (!g.getQuit()) {
        fpsTimer.start();
        g.clear();

	// Create new level only when needed
        if (levelChanged)
        {
            shape.createLevel(startLoc);
            levelChanged = false;
            allBlocks = shape.getAllActiveShapes();

        }
        shape.drawLevel(startLoc, g);
        shooter.drawBall(p, size, c, g);

        //when clicked x and y calculates distance from start to click point
        if (g.mouseClick())
        {
            clickPos = g.getMouseClick();
            p.y = 50;
            p.x = 500;
            xPos = p.x;
            yPos = p.y;
            xDist = clickPos.x - p.x;
            yDist = clickPos.y - p.y;

            shooter.setMagnitude(13);
            shooter.setDirection(atan(static_cast<double>(xDist) / yDist));

            c = black;
            isFalling = true;
            firstHit = false;
        }

        // when clicked
        if (isFalling)
        {
            // apply gravity
            if (firstHit)
            {
                shooter.apply(GRAVITY);
            }
            // change y and x pos based on magnitude and direction
            yPos += shooter.getMagnitude() * cos(shooter.getDirection());
            p.y = static_cast<int>(yPos);
            if (p.y < size + 3)
            {
                p.y = size + 3;
            }

            xPos += shooter.getMagnitude() * sin(shooter.getDirection());
            p.x = static_cast<int>(xPos);
            if (p.x < size + 3)
            {
                p.x = size + 3;
            }
            else if (p.x > g.getCol() - size - 3)
            {
                p.x = g.getCol() - size - 3;
            }


            // update flag positions
            flag.update(p.x, p.y, size, shooter.getForce());

            //if hit left wall
            if (p.x < 15)
            {
                shooter.setDirection(2 * M_PI - shooter.getDirection());
            }
            //if hit right wall
            else if (p.x > 985)
            {
                shooter.setDirection(2 * M_PI - shooter.getDirection());
            }
            for(int i = 0; i < allBlocks.size(); ++i)
            {
                if (HitBox::isHit(shooter.getHitBox(), allBlocks[i].getHitBox()))
                { // if hit box detected, then check if flags also detect hit in correct direction
                    flagNum = flag.isHit(g);
                    if (flagNum != -1)
                    {
                        // if first hit, turn on gravity
                        if (!firstHit)
                        {
                            firstHit = true;
                        }
                        shooter.setMagnitude(shooter.getMagnitude() - 0.4);
                        if (shooter.getMagnitude() < 0)
                        {
                            shooter.setMagnitude(0);
                            isFalling = false;
                        }
                        g.initSound("sounds/soundHit.wav");
                        g.playSound("sounds/soundHit.wav");
                        cout << "square hit !!" << endl;
                        allBlocks.at(i).decreaseLife();
                        cout << allBlocks.at(i).getLife() << endl;

                    }

                    if (flagNum == 0)
                    { //top hit
                        cout << "top flag initial: " << shooter.getDirection() << endl;
                        shooter.setDirection(M_PI - shooter.getDirection());
                        cout << "top flag new: " << shooter.getDirection() << endl;
                    }
                    else if (flagNum == 2)
                    { //bottom hit
                        cout << "bottom flag: " << shooter.getDirection() << endl;
                        shooter.setDirection(3 * M_PI - shooter.getDirection());
                        // if direction is close to straight up/down, set it to the closest PI/8 value so that it doesn't get stuck bouncing up/down
                        if (shooter.getDirection() >= 7.0 * M_PI / 8.0 && shooter.getDirection() <= M_PI)
                        {
                            shooter.setDirection(7.0 * M_PI / 8.0);
                        }
                        else if (shooter.getDirection() >= M_PI && shooter.getDirection() <= 9.0 * M_PI / 8.0)
                        {
                            shooter.setDirection(9.0 * M_PI / 8.0);
                        }
                        cout << "bottom flag new: " << shooter.getDirection() << endl;
                    }

                    else if (flagNum == 1)
                    { //right hit
                        cout << "right flag: " << shooter.getDirection() << endl;
                        shooter.setDirection(0 - shooter.getDirection());
                        if ((shooter.getDirection() > 15.0 / 16.0 * M_PI && shooter.getDirection() < 17.0 / 16.0 * M_PI) || (shooter.getDirection() > 31.0 / 16.0 * M_PI) || shooter.getDirection() < 1.0 / 16.0 * M_PI)
                        {
                            shooter.apply(PUSHLEFT);
                        }
                        cout << "right flag new: " << shooter.getDirection() << endl;
                    }
                    else if (flagNum == 3)
                    { //left hit
                        cout << "left flag: " << shooter.getDirection() << endl;
                        shooter.setDirection(0 - shooter.getDirection());
                        if ((shooter.getDirection() > 15.0 / 16.0 * M_PI && shooter.getDirection() < 17.0 / 16.0 * M_PI) || shooter.getDirection() > 31.0 / 16.0 || shooter.getDirection() < 1 / 16.0 * M_PI)
                        {
                            shooter.apply(PUSHRIGHT);
                        }
                        cout << "left flag new: " << shooter.getDirection() << endl;
                    }

                    else if (flagNum == 4)
                    { // top right corner hit
                        cout << "TOP RIGHT CORNER" << endl;
                        shooter.setDirection(shooter.getDirection() - M_PI);
                    }
                    else if (flagNum == 5)
                    { // bottom right corner hit
                        cout << "BOTTOM RIGHT CORNER" << endl;
                        shooter.setDirection(M_PI + shooter.getDirection());
                    }
                    else if (flagNum == 6)
                    { // bottom left corner hit
                        cout << "BOTTOM LEFT CORNER" << endl;
                        shooter.setDirection(M_PI + shooter.getDirection());
                    }
                    else if (flagNum == 7)
                    { // top left corner hit
                        cout << "TOP LEFT CORNER" << endl;
                        shooter.setDirection(shooter.getDirection() - M_PI);
                    }
                }
            }

            // If frame finished early syncing with fps
            frameTicks = fpsTimer.getTicks();
            if (frameTicks < SCREEN_TICKS_PER_FRAME)
            {
                // Wait remaining time
                SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
            }
        }

        //if the position is above 980 (ball is at bottom of the screen), then reset ball to top and draw a new level
        if (p.y > 980){
            g.clear();
            cout << "POSITION RESET" << endl;
            //reset the ball position to the top
            p.x = 500;
            p.y = 50;
            isFalling = false;
            // redraw the ball and update/draw the new level
            shooter.drawBall(p, size, c, g);
            shape.nextLevel();
            levelChanged = true;
            shape.drawLevel(startLoc, g);
        }

        //while in the game loop, update the screen
        g.Sleep(10);
        ++countedFrames;
        g.update();
    }
    return 0;
}
