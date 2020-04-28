#ifndef _OPEN_TOT_PLAYER_SPRITE_HPP_
#define _OPEN_TOT_PLAYER_SPRITE_HPP_

#include "mapsprite.hpp"

class PlayerSprite : public MapSprite
{
public:
    PlayerSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~PlayerSprite() override;

    virtual void draw(const Window &window) const override;
    virtual void doAction(Map *map) = 0;
};

#endif