#include "costumeselectsprite.hpp"
#include "playersprite.hpp"

CostumeSelectSprite::CostumeSelectSprite(SDL_Texture *texture, const std::string &animationKey, CostumeType costumeType)
    : AnimatedMapSprite(texture, animationKey)
    , type(costumeType)
{}

CostumeSelectSprite::~CostumeSelectSprite()
{}

void CostumeSelectSprite::onCollide(MapSprite *other)
{
    if(!other->isPlayer())
        return;

    PlayerSprite *player = static_cast<PlayerSprite *> (other);
    player->setCostumeType(type);
}
