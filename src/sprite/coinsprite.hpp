#ifndef _OPEN_TOT_COIN_SPRITE_HPP_
#define _OPEN_TOT_COIN_SPRITE_HPP_

#include "objectsprite.hpp"

class Tileset;

class CoinSprite : public ObjectSprite
{
private:
    static const SDL_Rect COIN_INITIAL_SRC;
    static const unsigned int COIN_ANIMATION_HEIGHT;
    static const unsigned int COIN_ANIMATION_DURATION;
    static const unsigned short int COIN_NUM_ANIMATIONS;
    static const SDL_Point SHADOW_SRC_CENTER;

public:
    CoinSprite(Tileset *tileset, const SDL_Point &mapPos);

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;
    ObjectType getType() const override;
    bool isBlocking() const override;

private:
    unsigned int animationDeltaTime;
};

#endif