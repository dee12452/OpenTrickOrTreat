#ifndef _OPEN_TOT_DELTA_ANIMATION_HPP_
#define _OPEN_TOT_DELTA_ANIMATION_HPP_

#include "animation.hpp"
#include "util/timer.hpp"

class DeltaAnimation : public Animation
{
public:
    DeltaAnimation(const SDL_Rect & initialSrc
            , int deltaX
            , int deltaY
            , int deltaW
            , int deltaH
            , unsigned int iterationsBeforeReset
            , unsigned int animationDelayMs);
    ~DeltaAnimation() override;

    Animation * copy() override;
    const SDL_Rect & getNext() override;
    void reset() override;

private:
    SDL_Rect initialSrc, src;
    int deltaX, deltaY, deltaW, deltaH;
    unsigned int currentIteration;
    unsigned int iterationsBeforeReset;
    Timer animationTimer;
};

#endif

