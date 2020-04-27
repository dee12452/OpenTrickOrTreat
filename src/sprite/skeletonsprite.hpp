#ifndef _OPEN_TOT_SKELETON_SPRITE_HPP_
#define _OPEN_TOT_SKELETON_SPRITE_HPP_

#include "playersprite.hpp"
#include "util/timer.hpp"

class SkeletonSprite : public PlayerSprite
{
private:
    static const SDL_Rect SKELETON_INITIAL_SRC;
    static const int ANIMATION_SKIP;
    static const unsigned int ANIMATION_DELAY;
    static const unsigned int SKELETON_ANIMATIONS;
    static const unsigned int KEYS_ANIMATION_DURATION;
    static const SDL_Rect KEYS_INITIAL_SRC;

public:
    SkeletonSprite();

    void draw(const Window &window) override;
    void update(
        unsigned int deltaTime,
        const std::vector<std::vector<unsigned int>> &tileGrid, 
        Tileset *tileset) override;
    void doAction() override;

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
    Timer keyTimer;
    bool keysActive;
};

#endif