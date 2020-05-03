#ifndef _OPEN_TOT_MONSTER_SPRITE_HPP_
#define _OPEN_TOT_MONSTER_SPRITE_HPP_

#include "playersprite.hpp"

class MonsterSprite : public PlayerSprite
{
private:
    static const SDL_Rect MONSTER_INITIAL_SRC;
    static const short int MONSTER_NUMBER_MOVE_ANIMATIONS;
    static const unsigned int SMASHING_ANIMATION_DURATION;
    static const unsigned short int NUMBER_SMASHING_ANIMATIONS;
    static const int MONSTER_HITBOX_Y_OFFSET;
    static const int MONSTER_HITBOX_W;
    static const int MONSTER_HITBOX_H;

public:
    MonsterSprite();

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
    bool smashing;
    unsigned int smashingAnimationDelta;
};

#endif