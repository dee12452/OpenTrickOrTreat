#ifndef _OPEN_TOT_ROTATE_SPRITE_HPP_
#define _OPEN_TOT_ROTATE_SPRITE_HPP_

#include "mapsprite.hpp"

class SpellSprite : public MapSprite
{
private:
    static const std::vector<SDL_Rect> SPELL_ANIMATION_SOURCES; 

public:
    SpellSprite();

    void update(unsigned int deltaTime, Map *map) override;
    void draw(const Window &window) const override;

    void resetAnimation();
    void setAnimationFrame(unsigned short int currentSpellAnimation);

    double getAngle() const;
    void setAngle(double angle);

private:
    unsigned short int currentAnimation;
    double angle;
};

#endif