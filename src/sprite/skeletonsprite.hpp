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
    void onStopX(int previousSpeed) override;
    void onStopY(int previousSpeed) override;
    void onMoveX() override;
    void onMoveY() override;
    bool canMove(
        const std::vector<std::vector<unsigned int>> &tileGrid, 
        Tileset *tileset) override;

private:
    Timer animationTimer;
};

#endif