#ifndef _OPEN_TOT_ANIMATED_MAP_SPRITE_HPP_
#define _OPEN_TOT_ANIMATED_MAP_SPRITE_HPP_

#include "mapsprite.hpp"
#include "animation/animationmanager.hpp"

class AnimatedMapSprite : public MapSprite
{
public:
    AnimatedMapSprite(SDL_Texture *texture, const std::string &animationKey);
    ~AnimatedMapSprite() override;

protected:
    void onUpdate(Map *currentMap) override;

private:
    Animation *animation;
};

#endif
