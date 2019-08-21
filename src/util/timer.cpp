#include "timer.hpp"
#include <SDL2/SDL_timer.h>

Timer::Timer() : Timer(0)
{}

Timer::Timer(unsigned int targetMs)
    : targetMillis(targetMs)
{}

void Timer::reset()
{
    startMillis = SDL_GetTicks();
    endMillis = SDL_GetTicks();
}

bool Timer::check()
{
    return getElapsedMillis() >= targetMillis;
}

unsigned int Timer::getTargetMillis() const
{
    return targetMillis;
}

void Timer::setTargetMillis(unsigned int targetMs)
{
    targetMillis = targetMs;
}

unsigned int Timer::getElapsedMillis()
{
    endMillis = SDL_GetTicks();
    if(endMillis < startMillis)
    {
        reset();
    }
    return endMillis - startMillis;
}
