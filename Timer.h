//
// Created by Erick on 11/17/2024.
//

#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

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
