#ifndef _OPEN_TOT_VAMPIRE_SPRITE_HPP_
#define _OPEN_TOT_VAMPIRE_SPRITE_HPP_

#include "playersprite.hpp"

class VampireSprite : public PlayerSprite
{
private:
    static const unsigned short int VAMPIRE_NUM_WALKING_ANIMATIONS;
    static const int VAMPIRE_HITBOX_Y_OFFSET;
    static const int VAMPIRE_HITBOX_W;
    static const int VAMPIRE_HITBOX_H;
    static const SDL_Rect VAMPIRE_INITIAL_SRC;
    static const unsigned int VAMPIRE_FLAP_ANIMATION_DURATION;
    static const unsigned short int VAMPIRE_BAT_ANIMATION_INDEX;

public:
    VampireSprite();

    void update(unsigned int deltaTime, Map *map) override;
    void stop() override;
    void doAction(Map *map) override;
    CostumeType getCostume() const override;

protected:
    bool canMove(Map *map, const SDL_Point &pos) const override;

    SDL_Rect getHitbox() const override;

private:
    unsigned int vampireFlapDeltaTime;
};

#endif