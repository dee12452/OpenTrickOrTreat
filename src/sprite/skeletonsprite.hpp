#ifndef _OPEN_TOT_SKELETON_SPRITE_HPP_
#define _OPEN_TOT_SKELETON_SPRITE_HPP_

#include "playersprite.hpp"

class SkeletonSprite : public PlayerSprite
{
private:
    static const SDL_Rect SKELETON_INITIAL_SRC;
    static const unsigned int SKELETON_ANIMATIONS;
    static const unsigned int KEYS_ANIMATION_DURATION;
    static const SDL_Rect KEY_INITIAL_SRC;
    static const unsigned int KEYS_ANIMATION_DELAY;
    static const unsigned short int DEFAULT_KEY_SPEED;
    static const int KEY_BUFFER;

public:
    SkeletonSprite();
    ~SkeletonSprite() override;

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;
    void doAction(Map *map) override;

protected:
    void onMoveX() override;
    void onMoveY() override;
    bool canMove(Map *map, int x, int y) override;

private:
    unsigned int keyDuration;
    unsigned int keyAnimationDeltaTime;
    bool keysActive;
    std::vector<MapSprite *> keys;

    void resetKeys() const;
    void animateKey(MapSprite *key, unsigned int deltaTime);
    void unlockDoors(Map *map) const;
};

#endif