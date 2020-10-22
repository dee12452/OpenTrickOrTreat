#ifndef _OPEN_TOT_STAR_BALL_SPRITE_HPP_
#define _OPEN_TOT_STAR_BALL_SPRITE_HPP_

#include "objectsprite.hpp"

class Tileset;

class StarBallSprite : public ObjectSprite
{
private:
    static const SDL_Rect STAR_BALL_INITIAL_SRC;
    static const unsigned int STAR_BALL_ANIMATION_DURATION;
    static const unsigned short int STAR_BALL_NUM_ANIMATIONS;
    static const SDL_Point SHADOW_SRC_CENTER;

public:
    StarBallSprite(Tileset *tileset, const SDL_Point &mapPos);

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;
    ObjectType getType() const override;
    bool isBlocking() const override;

private:
    unsigned int animationDeltaTime;
};

#endif