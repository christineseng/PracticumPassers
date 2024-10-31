// Name        : graphicsTest2.cpp
// Author      : Erick Martinez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
#include "Objects.h"
#include "force.h"


//Ball Class----------------------------------------------------
void Ball::drawBall(point loc, SDL_Plotter& win)
{
    for (double i = -10; i <= 10; i += 0.1)
    {
        for (double j = -10; j <= 10; j += 0.1)
        {
            if (i * i + j * j <= 10 * 10)
            {
                win.plotPixel(round(loc.x + i), round(loc.y + j), c);
            }
        }
    }
}

void Ball::drawBall(point loc, int size, color c, SDL_Plotter& win)
{
    for (double i = -size; i <= size; i += 0.1)
    {
        for (double j = -size; j <= size; j += 0.1)
        {
            if (i * i + j * j <= size * size)
            {
                win.plotPixel(round(loc.x + i), round(loc.y + j), c);
            }
        }
    }
}

/*
void Ball::ballFalling(point ballLoc, point clickPos, int velocity, SDL_Plotter& win)
{
    force f;
    color black, red;
    black.R = 0;   black.B = 0;   black.G = 0;
    red.R = 255;   red.B = 0;     red.G = 0;

    double xPos;
    double yPos;
    int xDist;
    int yDist;
    int size = 10;
    bool isFalling = false;

    //x and y calculates distance from start to click point
    ballLoc.x = 500;
    ballLoc.y = 50;
    xPos = ballLoc.x;
    yPos = ballLoc.y;
    xDist = clickPos.x - ballLoc.x;
    yDist = clickPos.y - ballLoc.y;

    //sets magnitude based on how far from start you click
    f.setMagnitude(sqrt(pow(xDist, 2) + pow(yDist, 2)) / 60);
    f.setDirection(atan(static_cast<double>(xDist) / yDist));
    //shooter.drawBall(ballLoc, win);
    c = black;
    drawBall(ballLoc, size, c, win);
    isFalling = true;

    //Calculate Velocity and Magnitude when clicked
    //change y and x pos based on magnitude and direction
    if(isFalling)
    {
        yPos += f.getMagnitude() * cos(f.getDirection());
        ballLoc.y = static_cast<int>(yPos);
        xPos += f.getMagnitude() * sin(f.getDirection());
        ballLoc.x = static_cast<int>(xPos);

        if (ballLoc.x <= 10 || ballLoc.x >= 990 || ballLoc.y <= 10 || ballLoc.y >= 990)
        {
            c = red;
            isFalling = false;
            drawBall(ballLoc, size, c, win);
        }
    }
}
*/

//BLOCK CLASS----------------------------------------------------
void Block::drawSquare(point loc, int length, int width, color c, SDL_Plotter& win)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Plot each pixel in the square based on the starting location (loc)
            win.plotPixel(loc.x + i, loc.y + j, c.R, c.G, c.B);
        }
    }
}

void Block::drawTraingle(point loc, int size, color c, SDL_Plotter& g)
{
}
