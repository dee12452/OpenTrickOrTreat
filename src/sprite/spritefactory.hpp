#ifndef _OPEN_TOT_SPRITE_FACTORY_HPP_
#define _OPEN_TOT_SPRITE_FACTORY_HPP_

#include "mapsprite.hpp"
#include "map.hpp"

class SpriteFactory
{
public:
    static MapSprite * generateSprite(const Consumable *consumable);

private:
    SpriteFactory();
};

#endif
