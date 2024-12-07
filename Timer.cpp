/*
* Authors: Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas, Nolan Schirripa
* Assignment Title:  Group Project (Timer.cpp)
* Assignment Description: defines Timer class that can be used to set ticks and frame rate
* Due Date: 12/09/2024
* Date Created: 10/31/2024
* Date Last Modified: 12/07/2024
*/

#include "Timer.h"

Timer::Timer()
{
    //Initialize the variables
    mStartTicks = 0;
    mStarted = false;
}

void Timer::start()
{
    //Start the timer
    mStarted = true;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    mStarted = false;

    //Reset Ticks
    mStartTicks = 0;
}

int Timer::getTicks()
{
    //The actual timer time
    int time = 0;

    //If the timer is running
    if (mStarted)
    {
        //Return the current time minus the start time
        time = SDL_GetTicks() - mStartTicks;
    }
    return time;
}
