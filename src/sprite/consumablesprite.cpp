#include "consumablesprite.hpp"

ConsumableSprite::ConsumableSprite(SDL_Texture *texture, const std::string &animationKey, ConsumableType consumableType)
    : AnimatedMapSprite(texture, animationKey)
    , type(consumableType)
{}

ConsumableSprite::~ConsumableSprite()
{}

void ConsumableSprite::onCollide(MapSprite *otherSprite)
{
    if(otherSprite->isPlayer())
    {
        setDisable(true);
    }
}
