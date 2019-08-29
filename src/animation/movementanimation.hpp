#ifndef _OPEN_TOT_MOVEMENT_ANIMATION_HPP_
#define _OPEN_TOT_MOVEMENT_ANIMATION_HPP_

#include "animation.hpp"

class MovementAnimation : public Animation
{
public:
    MovementAnimation(const SDL_Rect *rects, unsigned short int size);
    ~MovementAnimation() override;

    Animation * copy() override;
    const SDL_Rect & getNext() override;
    void reset() override;

private:
    std::vector<SDL_Rect> srcRects;
    unsigned short int currentAnimIndex;
};

#endif
