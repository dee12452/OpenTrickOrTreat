#ifndef _OPEN_TOT_WITCH_SPRITE_HPP_
#define _OPEN_TOT_WITCH_SPRITE_HPP_

#include "playersprite.hpp"
#include "spellsprite.hpp"

class WitchSprite : public PlayerSprite
{
private:
    static const short int WITCH_NUMBER_MOVE_ANIMATIONS;
    static const SDL_Rect WITCH_INITIAL_SRC;
    static const unsigned int SPELL_ANIMATION_DELAY;
    static const unsigned short int NUMBER_SPELL_ANIMATIONS;

public:
    WitchSprite();
    
    void update(unsigned int deltaTime, Map *map) override;
    void draw(const Window &window) const override;
    void doAction(Map *map) override;

protected:
    void onStopX(int previousSpeed) override;
    void onStopY(int previousSpeed) override;
    void onMoveX() override;
    void onMoveY() override;
    bool canMove(Map *map) override;

private:
    SpellSprite spell;
    bool usingSpell;
    Timer spellTimer;
    unsigned short int currentSpellAnimation;
};

#endif