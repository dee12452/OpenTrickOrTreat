#ifndef _OPEN_TOT_CONSUMABLE_SPRITE_HPP_
#define _OPEN_TOT_CONSUMABLE_SPRITE_HPP_

#include "animatedmapsprite.hpp"

enum ConsumableType { NONE, COIN, CANDY, STAR_BALL };

class ConsumableSprite : public AnimatedMapSprite
{
public:
    ConsumableSprite(SDL_Texture *texture, const std::string &animationKey, ConsumableType consumableType);
    ~ConsumableSprite() override;

protected:
    void onCollide(MapSprite *otherSprite) override;

private:
    ConsumableType type;
};

#endif
