/*
* Author: Nolan Schirripa, Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas
* Assignment Title:  Group Project (Ball.cpp)
* Assignment Description: defines ball class that can bounce off blocks and walls
* Due Date: 12/09/2024
* Date Created: 10/25/2024
* Date Last Modified: 12/07/2024
*/


#include "Ball.h"

void Ball::drawBall(point loc, int size, color c, SDL_Plotter& win)
{
    location = loc;
    hb.setPoint(loc);
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
