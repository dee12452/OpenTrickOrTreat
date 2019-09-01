#ifndef _OPEN_TOT_STAIRS_INTERACTION_SPRITE_HPP_
#define _OPEN_TOT_STAIRS_INTERACTION_SPRITE_HPP_

#include "interactionsprite.hpp"

class StairsInteractionSprite : public InteractionSprite
{
public:
    StairsInteractionSprite(const SDL_Rect &dstRect, int property);
    ~StairsInteractionSprite() override;

protected:
    void onInteract(PlayerSprite *player) override;
};

#endif
