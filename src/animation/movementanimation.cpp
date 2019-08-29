#include "movementanimation.hpp"

MovementAnimation::MovementAnimation(const SDL_Rect *rects, unsigned short int size)
    : currentAnimIndex(0)
{
    for(unsigned short int i = 0; i < size; i++)
    {
        srcRects.push_back(rects[i]);
    }
}

MovementAnimation::~MovementAnimation()
{}

Animation * MovementAnimation::copy()
{
    SDL_Rect rects[srcRects.size()];
    for(unsigned short int i = 0; i < srcRects.size(); i++)
    {
        rects[i] = srcRects[i];
    }
    return new MovementAnimation(rects, srcRects.size());
}

const SDL_Rect & MovementAnimation::getNext()
{
    const SDL_Rect &next = srcRects[currentAnimIndex];
    currentAnimIndex++;
    if(currentAnimIndex >= srcRects.size())
    {
        currentAnimIndex = 0;
    }
    return next;
}

void MovementAnimation::reset()
{
    currentAnimIndex = 0;
}
