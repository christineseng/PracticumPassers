// Name        : graphicsTest2.cpp
// Author      : Erick Martinez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
#include "Objects.h"
#include "force.h"
#include "flag.h"

//Ball Class----------------------------------------------------
void Ball::drawBall(point loc, SDL_Plotter& win)
{
    color c;
    c.R = 0;
    c.B = 0;
    c.G = 0;
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

//called in game.cpp
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

void Block::drawLine(point loc1, point loc2, color c, SDL_Plotter& g)
{
    int changeInX = loc2.x - loc1.x;
    int changeInY = loc2.y - loc1.y;

    int steps;

    if (changeInX >= changeInY)
    {
        steps = changeInX;
    }
    else
    {
        steps = changeInY;
    }

    double xIncrease = changeInX / static_cast<double>(steps);
    double yIncrease = changeInY / static_cast<double>(steps);

    double x;
    double y;
    x = loc1.x;
    y = loc1.y;

    for (int i = 0; i <= steps; ++i)
    {
        g.plotPixel(round(x), round(y), c);
        x += xIncrease;
        y += yIncrease;
    }
}

double Block::distance(point loc1, point loc2)
{
    double distance;
    distance = sqrt(pow(loc1.x - loc2.x, 2.0) + pow(loc1.y - loc2.y, 2.0));
    return distance;
}

void Block::drawTriangle(point topVertex, point leftVertex, point rightVertex, color c, SDL_Plotter& g)
{
    int sideLength;
    int height;
    int offset; //distance from center to edges
    point start;
    point end;

    sideLength = distance(topVertex, leftVertex);
    height = (sqrt(3.0) / 2.0) * sideLength;

    for (int y = 0; y <= height; ++y)
    {
        offset = (y / static_cast<double>(height)) * (sideLength / 2.0);
        start.x = topVertex.x - offset;
        start.y = topVertex.y + y;
        end.x = topVertex.x + offset;
        end.y = topVertex.y + y;
        drawLine(start, end, c, g);
    }
}

void Ball::ballFalling(point clickPos, SDL_Plotter& win)
{
    //DATA ABSTRACTION-------------------------------------------------
    color red;
    red.R = 255;
    red.B = 0;
    red.G = 0;
    bool isFalling = true;
    force f;
    int xDist, yDist;
    double xPos, yPos;
    int size = 10;
    point ballLoc;
    //-LOGIC------------------------------------------------------------
    clickPos = win.getMouseClick();
    ballLoc.y = 50;
    ballLoc.x = 500;
    xPos = ballLoc.x;
    yPos = ballLoc.y;
    xDist = clickPos.x - ballLoc.x;
    yDist = clickPos.y - ballLoc.y;
    //sets magnitude based on how far from start you click
    f.setMagnitude(sqrt(pow(xDist, 2) + pow(yDist, 2)) / 60);
    f.setDirection(atan(static_cast<double>(xDist) / yDist));
    drawBall(ballLoc, win);
    do
    {
        //change y and x pos based on magnitude and direction
        yPos += f.getMagnitude() * cos(f.getDirection());
        ballLoc.y = static_cast<int>(yPos);
        xPos += f.getMagnitude() * sin(f.getDirection());
        ballLoc.x = static_cast<int>(xPos);

        if (ballLoc.x <= 10 || ballLoc.x >= 990 || ballLoc.y <= 10 || ballLoc.y >= 990)
        {
            isFalling = false;
            drawBall(ballLoc, size, red, win);
        }
    }
    while (isFalling);

    if (isFalling) {
        //change y and x pos based on magnitude and direction
        yPos += f.getMagnitude() * cos(f.getDirection());
        ballLoc.y = static_cast<int> (yPos);
        xPos += f.getMagnitude() * sin(f.getDirection());
        ballLoc.x = static_cast<int> (xPos);

        if (ballLoc.x <= 10 || ballLoc.x >= 990 || ballLoc.y <= 10 || ballLoc.y >= 990){
            isFalling = false;
            drawBall(ballLoc, size, red, win);
        }
    }
}
