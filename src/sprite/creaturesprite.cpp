#include "creaturesprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"

const SDL_Rect CreatureSprite::CREATURE_INITIAL_SRC = {0, 0, 56, 56};
const unsigned short int CreatureSprite::CREATURE_WALK_ANIMATIONS = 8;
const int CreatureSprite::CREATURE_HITBOX_Y_OFFSET = 12;
const int CreatureSprite::CREATURE_HITBOX_W = 30;
const int CreatureSprite::CREATURE_HITBOX_H = 30;

CreatureSprite::CreatureSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_CREATURE),
        CREATURE_INITIAL_SRC,
        CREATURE_INITIAL_SRC,
        CREATURE_WALK_ANIMATIONS,
        CREATURE_INITIAL_SRC.h)
    , jumping(false)
    , swimming(false)
{}

void CreatureSprite::update(unsigned int deltaTime, Map *map)
{

}

void CreatureSprite::doAction(Map *map)
{
    if(jumping) return;
    
}

CostumeType CreatureSprite::getCostume() const
{
    return CREATURE;
}

SDL_Rect CreatureSprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - CREATURE_HITBOX_W / 2,
        center.y - CREATURE_HITBOX_H / 2 + CREATURE_HITBOX_Y_OFFSET,
        CREATURE_HITBOX_W,
        CREATURE_HITBOX_H
    };
}