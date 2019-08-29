#include "deltaanimation.hpp"

DeltaAnimation::DeltaAnimation(const SDL_Rect & initSrc
        , int dX
        , int dY
        , int dW
        , int dH
        , unsigned int iterations
        , unsigned int animDelayMs)
    : initialSrc(initSrc)
    , src(initSrc)
    , deltaX(dX)
    , deltaY(dY)
    , deltaW(dW)
    , deltaH(dH)
    , currentIteration(0)
    , iterationsBeforeReset(iterations)
    , animationTimer(animDelayMs)
{}

DeltaAnimation::~DeltaAnimation()
{}

Animation * DeltaAnimation::copy()
{
    return new DeltaAnimation(this->initialSrc
            , this->deltaX
            , this->deltaY
            , this->deltaW
            , this->deltaH
            , this->iterationsBeforeReset
            , this->animationTimer.getTargetMillis());
}

const SDL_Rect & DeltaAnimation::getNext()
{
    if(animationTimer.check())
    {
        if(currentIteration >= iterationsBeforeReset)
        {
            currentIteration = 0;
            src = initialSrc;
        }
        else 
        {
            src.x += deltaX;
            src.y += deltaY;
            src.w += deltaW;
            src.h += deltaH;
            currentIteration++;
        }
        animationTimer.reset();
    }
    return src;
}

void DeltaAnimation::reset()
{
    currentIteration = 0;
    src = initialSrc;
}
