/*
* Ball.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: nolanschirripa
 */

#include "Ball.h"

//Ball Class----------------------------------------------------
void Ball::drawBall(point loc, SDL_Plotter& win)
{
    location = loc;
    //update hit box location and force so that they match the ball's
    hb.setPoint(loc);
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
