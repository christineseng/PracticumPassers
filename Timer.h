/*
* Authors: Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas, Nolan Schirripa
* Assignment Title:  Group Project (Timer.h)
* Assignment Description: declares Timer class that can be used to set ticks and frame rate
* Due Date: 12/09/2024
* Date Created: 10/31/2024
* Date Last Modified: 12/07/2024
*/

#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>

class Timer
{
public:
    //Constructers
    Timer();

    //Functions
    void start();
    void stop();
    int getTicks();
private:
    int mStartTicks;
    bool mStarted;
};

#endif //TIMER_H
