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
    static const SDL_Rect KEY_INITIAL_SRC;
    static const unsigned int KEYS_ANIMATION_DELAY;
    static const int DEFAULT_KEY_SPEED;
    static const int KEY_BUFFER;

public:
    SkeletonSprite();
    ~SkeletonSprite() override;

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;
    void doAction(Map *map) override;

protected:
    void onStopX(int previousSpeed) override;
    void onStopY(int previousSpeed) override;
    void onMoveX() override;
    void onMoveY() override;
    bool canMove(Map *map) override;

private:
    Timer animationTimer;
    Timer keyTimer;
    Timer keyAnimationTimer;
    bool keysActive;
    std::vector<MapSprite *> keys;

    void resetKeys() const;
    void animateKey(MapSprite *key) const;
    void unlockDoors(Map *map) const;
};

#endif