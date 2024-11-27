//
// Created by User on 11/13/2024.
//

#include "Block.h"
#include "SDL_Plotter.h"

//Constructors

Block::Block(): location(), life(1), blockColor(), shape("") {}
Block::Block(point loc, string s): location(loc), shape(s){
	life = rand() % 8 + 1;
	updateBlockColor();

    hb.setPoint(loc);
    hb.setLength(85);
    hb.setWidth(85);
}

//Member Functions

void Block::drawSquare(point loc, int size, color c, SDL_Plotter& win)
{
    hb.setPoint(loc);
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
    hb.setPoint(centroid);
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
    hb.setPoint(loc);
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

void Block::createLevel(point startLoc)
{
    //Data-Abstraction
    int size = 75;
    int randLocOne, randLocTwo, randLocThree;
    randLocOne = rand() % 281 + 39;
    randLocTwo = rand() % 281 + 359;
    randLocThree = rand() % 281 + 679;

    color red = {255, 0, 0};
    point loc1 = {randLocOne, startLoc.y - levelOffsetY};
    point loc2 = {randLocTwo, startLoc.y - levelOffsetY};
    point loc3 = {randLocThree, startLoc.y - levelOffsetY};
    vector<string> shapes(3);

    for (int i = 0; i < 3; ++i) {
        int state = rand() % 10;
        if (state >= 0 && state < 4) state = 1;
        else if (state < 8) state = 2;
        else if (state <= 9) state = 3;

        if (state == 1) shapes[i] = "Circle";
        if (state == 2) shapes[i] = "Square";
        if (state == 3) shapes[i] = "Triangle";

    }


    allActiveShapes.emplace_back(loc1, shapes[0]); //emplace_back() is like push_back() but for pass by refrence
    allActiveShapes.emplace_back(loc2, shapes[1]);
    allActiveShapes.emplace_back(loc3, shapes[2]);

    levelOffsetY += 100;
}

void Block::drawLevel(point startLoc, SDL_Plotter& g)
{
    //Data-Abstraction
    int size = 75;

    //Draw random Shapes to the created Level
    if (!allActiveShapes.empty())
    {
        for(int i = 0; i < allActiveShapes.size(); ++i)
        {
            if(allActiveShapes[i].shape == "Circle")
            {
                drawCircle(allActiveShapes[i].location, size / 2, allActiveShapes[i].getColor(), g);
            }
            if(allActiveShapes[i].shape == "Square")
            {
                drawSquare(allActiveShapes[i].location, size, allActiveShapes[i].getColor(), g);
            }
            if(allActiveShapes[i].shape == "Triangle")
            {
                drawTriangle(allActiveShapes[i].location, size, allActiveShapes[i].getColor(), g);
            }
        }
    }

}

void Block::nextLevel()
{
    currentLevel++;
}


void Block::decreaseLife() {
	if (life > 0) {
		--life;
		cout << "Life decreased to: " << life << endl;
		updateBlockColor();
	}
}

void Block::updateBlockColor() {
	switch (life) {
	case 8: {
		blockColor = {255, 0, 0}; //red
		break;
	}
	case 7: {
		blockColor = {255, 51, 153}; //hot red/pink
		break;
	}
	case 6: {
		blockColor = {255, 128, 0}; //orange
		break;
	}
	case 5: {
		blockColor = {255, 230, 20}; //yellowish
		break;
	}
	case 4: {
		blockColor = {51, 255, 51}; //green
		break;
	}
	case 3: {
		blockColor = {0, 255, 128}; //
		break;
	}
	case 2: {
		blockColor = {255, 255, 0};
		break;
	}
	case 1: {
		blockColor = {102, 178, 255};
		break;
	}
	case 0: {
		blockColor = {0, 0, 0}; //black for testing
		break;
	}
	default:
		break;

	}

}

void Block::setAllActiveShapesLife (int l, int index) {
	allActiveShapes.at(index).setLife(l);

}

