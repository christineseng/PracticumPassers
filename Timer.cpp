//
// Created by Erick on 11/17/2024.
//

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
