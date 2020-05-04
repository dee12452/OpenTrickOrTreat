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

public:
    CreatureSprite();

    void update(unsigned int deltaTime, Map *map) override;
    void doAction(Map *map) override;
    CostumeType getCostume() const override;

protected:
    SDL_Rect getHitbox() const override;

private:
    bool jumping;
    bool swimming;
};

#endif