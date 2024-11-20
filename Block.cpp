//
// Created by User on 11/13/2024.
//

#include "Block.h"
#include "SDL_Plotter.h"

//Constructors
Block::Block(): location(), c(), life(0), shape("") {}
Block::Block(point loc, color col, int l, string s): location(loc), c(col), life(l), shape(s){
    hb.setPoint(loc);
    hb.setLength(85);
    hb.setWidth(85);
}

//Member Functions
void Block::drawSquare(point loc, int size, color c, SDL_Plotter& win)
{
    int length, width;
    shape = "Square";
    location.x = loc.x;
    location.y = loc.y;

    length = size, width = size;
    // Calculate the top-left corner of the square based on the center
    int startX = loc.x - length / 2;
    int startY = loc.y - width / 2;

    // Draw the square starting from the calculated top-left corner
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            win.plotPixel(startX + i, startY + j, c.R, c.G, c.B);
        }
    }
}

void Block::drawLine(point loc1, point loc2, color c, SDL_Plotter& g) const
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

double Block::distance(point loc1, point loc2) const
{
    double distance;
    distance = sqrt(pow(loc1.x - loc2.x, 2.0) + pow(loc1.y - loc2.y, 2.0));
    return distance;
}

void Block::drawTriangle(point centroid, int size, color c, SDL_Plotter& g)
{
    double height;
    point topVertex, leftVertex, rightVertex;
    point start, end;

    shape = "Triangle";
    location.x = centroid.x;
    location.y = centroid.y;

    height = (sqrt(3.0) / 2.0) * size;
    topVertex.x = centroid.x;
    topVertex.y = centroid.y - (2.0 / 3.0) * height;

    leftVertex.x = centroid.x - (size / 2.0);
    leftVertex.y = centroid.y + (1.0 / 3.0) * height;

    rightVertex.x = centroid.x + (size / 2.0);
    rightVertex.y = centroid.y + (1.0 / 3.0) * height;

    for (int y = 0; y <= height; ++y)
    {
        int offset = (y / static_cast<double>(height)) * (size / 2.0);

        // start and end points of the line to draw at this row
        start.x = topVertex.x - offset;
        start.y = topVertex.y + y;

        end.x = topVertex.x + offset;
        end.y = topVertex.y + y;

        // Draw the line for this row
        drawLine(start, end, c, g);
    }
}

void Block::drawCircle(point loc, int size, color c, SDL_Plotter& win)
{
    int x = 0;
    int y = size;
    int d = 3 - 2 * size;

    auto plotHorizontalLine = [&](int xStart, int xEnd, int yCoord)
    {
        for (int x = xStart; x <= xEnd; x++)
        {
            win.plotPixel(x, yCoord, c);
        }
    };

    while (x <= y)
    {
        // Draw horizontal spans to fill the circle
        plotHorizontalLine(loc.x - x, loc.x + x, loc.y + y); // Upper span
        plotHorizontalLine(loc.x - x, loc.x + x, loc.y - y); // Lower span
        plotHorizontalLine(loc.x - y, loc.x + y, loc.y + x); // Left span
        plotHorizontalLine(loc.x - y, loc.x + y, loc.y - x); // Right span

        // Update decision parameter and iterate
        if (d <= 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void Block::drawMirroredTriangle(point leftVertex, point rightVertex, point bottomVertex, color c, SDL_Plotter& g)
{
    int sideLength;
    int height;
    int offset; //distance from center to edges
    point start;
    point end;

    sideLength = distance(leftVertex, rightVertex);
    height = (sqrt(3.0) / 2.0) * sideLength;

    for (int y = 0; y <= height; ++y)
    {
        offset = ((height - y) / static_cast<double>(height)) * (sideLength / 2.0);
        start.x = bottomVertex.x - offset;
        start.y = bottomVertex.y + y;
        end.x = bottomVertex.x + offset;
        end.y = bottomVertex.y + y;
        drawLine(start, end, c, g);
    }
}

void Block::drawRandomShape(point loc, int size, color c, SDL_Plotter& g, int state)
{
    if (state >= 0 && state < 4) state = 1;
    else if (state < 8) state = 2;
    else if (state <= 9) state = 3;

    string shape = "default";

    switch (state)
    {
    case 1:
        {
            drawCircle(loc, size / 2, c, g);
            shape = "Circle";
            break;
        }
    case 2:
        {
            drawSquare(loc, size, c, g);
            shape = "Square";
            break;
        }
    case 3:
        {
            drawTriangle(loc, size, c, g);
            shape = "Triangle";
            break;
        }
    default:
        break;
    }
    Block currentShape(loc,c,size,shape);
    allActiveShapes.push_back(currentShape);

    //Once ran we should pushback block into 2D vector to store location,size,color etc.
    //Because some levels might have a differnt amount of objects spawning ie. not three
    //we need a boolean flag to differtiate rows(levels) in a 2D vector named allActiveShapes
    //We also need a way to update allActiveShapes to check if life levels of any shape has dropped below 0 if then NULL that pos
    //in drawLevel we need to iterate through this 2D vector to draw the correct amount of levels
    //If we reach NULL just skip that draw phase and move forward
    //
}

void Block::createLevel(point startLoc)
{
    shapeStates.clear();
    levelOffsetY += 50;

    shapeStates.push_back(rand() % 10);
    shapeStates.push_back(rand() % 10);
    shapeStates.push_back(rand() % 10);
}

void Block::drawLevel(point startLoc, SDL_Plotter& g)
{
    int size = 75;

    color red = {255, 0, 0};
    color blue = {0, 0, 255};
    color green = {0, 255, 0};

    point loc1 = {startLoc.x, startLoc.y - levelOffsetY};
    point loc2 = {startLoc.x - 250, startLoc.y - levelOffsetY};
    point loc3 = {startLoc.x + 250, startLoc.y - levelOffsetY};

    if (!shapeStates.empty())
    {
        drawRandomShape(loc1, size, red, g, shapeStates[0]);
        drawRandomShape(loc2, size, green, g, shapeStates[1]);
        drawRandomShape(loc3, size, blue, g, shapeStates[2]);
    }
}

void Block::nextLevel()
{
    currentLevel++;
}
