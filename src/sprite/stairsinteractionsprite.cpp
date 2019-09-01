#include "stairsinteractionsprite.hpp"

StairsInteractionSprite::StairsInteractionSprite(const SDL_Rect &dstRect, int property)
    : InteractionSprite(dstRect, property)
{}

StairsInteractionSprite::~StairsInteractionSprite()
{}

void StairsInteractionSprite::onInteract(PlayerSprite *player)
{
    player->setLocationZ(static_cast<unsigned int> (getProperty()));
}
