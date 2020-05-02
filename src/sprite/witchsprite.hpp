#ifndef _OPEN_TOT_WITCH_SPRITE_HPP_
#define _OPEN_TOT_WITCH_SPRITE_HPP_

#include "playersprite.hpp"
#include "spellsprite.hpp"

class WitchSprite : public PlayerSprite
{
private:
    static const short int WITCH_NUMBER_MOVE_ANIMATIONS;
    static const SDL_Rect WITCH_INITIAL_SRC;
    static const unsigned int SPELL_ANIMATION_DURATION;
    static const unsigned short int NUMBER_SPELL_ANIMATIONS;
    static const int WITCH_HITBOX_Y_OFFSET;
    static const int WITCH_HITBOX_W;
    static const int WITCH_HITBOX_H;

public:
    WitchSprite();
    
    void update(unsigned int deltaTime, Map *map) override;
    void draw(const Window &window) const override;
    void stop() override;
    void doAction(Map *map) override;
    CostumeType getCostume() const override;

protected:
    void onMoveX() override;
    void onMoveY() override;
    bool canMove(Map *map, int x, int y) override;

    SDL_Rect getHitbox() const override;

private:
    SpellSprite spell;
    bool usingSpell;
    unsigned int spellAnimationDelta;
};

#endif