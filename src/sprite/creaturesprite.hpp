#ifndef _OPEN_TOT_CREATURE_SPRITE_HPP_
#define _OPEN_TOT_CREATURE_SPRITE_HPP_

#include "playersprite.hpp"

class CreatureSprite : public PlayerSprite
{
private:
    static const SDL_Rect CREATURE_INITIAL_SRC;
    static const unsigned short int CREATURE_WALK_ANIMATIONS;
    static const int CREATURE_HITBOX_Y_OFFSET;
    static const int CREATURE_HITBOX_W;
    static const int CREATURE_HITBOX_H;
    static const int CREATURE_JUMP_HITBOX_OFFSET;
    static const unsigned int CREATURE_JUMP_ANIMATION_DURATION;
    static const unsigned short int CREATURE_JUMP_NUM_ANIMATIONS;
    static const unsigned int CREATURE_SPLASH_ANIMATION_DURATION;
    static const std::vector<SDL_Rect> CREATURE_SPASH_ANIMATION_SOURCES;

    static const unsigned short int CREATURE_SWIM_NUM_ANIMATIONS;
    static const unsigned int SWIM_ANIMATION_CYCLE_DURATION;

public:
    CreatureSprite();

    void update(unsigned int deltaTime, Map *map) override;
    void doAction(Map *map) override;
    void stop() override;
    CostumeType getCostume() const override;

protected:
    void onMoveX() override;
    void onMoveY() override;
    bool canMove(Map *map, int x, int y) const override;
    SDL_Rect getHitbox() const override;

private:
    bool jumping;
    bool swimming;
    unsigned int jumpingAnimationDelta;
    unsigned int splashAnimationDelta;
    SDL_Point jumpingPoint;
    unsigned int swimDeltaTime;
};

#endif