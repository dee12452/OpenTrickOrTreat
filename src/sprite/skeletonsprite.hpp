#ifndef _OPEN_TOT_SKELETON_SPRITE_HPP_
#define _OPEN_TOT_SKELETON_SPRITE_HPP_

#include "mapsprite.hpp"
#include "util/timer.hpp"

class SkeletonSprite : public MapSprite
{
private:
    static const SDL_Rect SKELETON_INITIAL_SRC;
    static const int ANIMATION_SKIP;
    static const unsigned int ANIMATION_DELAY;
    static const unsigned int SKELETON_ANIMATIONS;

public:
    SkeletonSprite();

protected:
    void onStopX(int previousSpeed);
    void onStopY(int previousSpeed);
    void onMoveX();
    void onMoveY();

private:
    Timer animationTimer;
};

#endif