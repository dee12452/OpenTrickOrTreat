#ifndef _OPEN_TOT_INTERACTION_SPRITE_HPP_
#define _OPEN_TOT_INTERACTION_SPRITE_HPP_

#include "playersprite.hpp"

class InteractionSprite : public MapSprite
{
public:
    InteractionSprite(const SDL_Rect dstRect, int property);
    virtual ~InteractionSprite() override;

    void draw(const Window &, Map *, const SDL_Rect &, unsigned int) override;

protected:
    int getProperty() const;

    void onCollide(MapSprite *other) override;
    virtual void onInteract(PlayerSprite *player) = 0;

private:
    int property;
};

#endif
