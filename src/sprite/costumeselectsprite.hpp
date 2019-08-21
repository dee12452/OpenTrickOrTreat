#ifndef _OPEN_TOT_COSTUME_SELECT_SPRITE_HPP_
#define _OPEN_TOT_COSTUME_SELECT_SPRITE_HPP_

#include "animatedmapsprite.hpp"

class CostumeSelectSprite : public AnimatedMapSprite
{
public:
    CostumeSelectSprite(SDL_Texture *texture, const std::string &animationKey, CostumeType costumeType);
    ~CostumeSelectSprite() override;

protected:
    void onCollide(MapSprite *other) override;

private:
    CostumeType type;
};

#endif
