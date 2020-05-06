#include "candysprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"
#include "playersprite.hpp"

const SDL_Rect CandySprite::CANDY_INITIAL_SRC = {0, 283, 36, 28};
const unsigned short int CandySprite::CANDY_HITBOX_W = 27;
const unsigned short int CandySprite::CANDY_HITBOX_H = 15;
const unsigned int CandySprite::CANDY_ANIMATION_DURATION = 450;
const unsigned short int CandySprite::CANDY_NUM_ANIMATIONS = 6;

CandySprite::CandySprite(Tileset *tileset, const SDL_Point &mapPos)
    : ObjectSprite(TextureManager::getInstance()->getTexture(Const::IMAGE_MISC),
    CANDY_INITIAL_SRC,
    CANDY_INITIAL_SRC)
    , animationDeltaTime(0)
{
    const int tileX = mapPos.x - mapPos.x % tileset->getTileWidth();
    const int tileY = mapPos.y - mapPos.y % tileset->getTileHeight();
    setX(tileX + tileset->getTileWidth() / 2 - getWidth() / 2);
    setY(tileY + tileset->getTileHeight() / 2 - getHeight() / 2);
}

void CandySprite::update(unsigned int deltaTime, Map *map)
{
    animationDeltaTime += deltaTime;
    if(animationDeltaTime > CANDY_ANIMATION_DURATION)
    {
        animationDeltaTime %= CANDY_ANIMATION_DURATION;
    }
    const unsigned short int animationIndex = animationDeltaTime / (CANDY_ANIMATION_DURATION / CANDY_NUM_ANIMATIONS);
    setSourceY(CANDY_INITIAL_SRC.y + CANDY_INITIAL_SRC.h * animationIndex);
    if(!consumed && !map->getPlayer()->isFlying() && isColliding(map->getPlayer()))
    {
        consumed = true;
    }
}

ObjectType CandySprite::getType() const
{
    return CANDY;
}

bool CandySprite::isBlocking() const
{
    return false;
}

SDL_Rect CandySprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - CANDY_HITBOX_W / 2,
        center.y - CANDY_HITBOX_H / 2,
        CANDY_HITBOX_W,
        CANDY_HITBOX_H
    };
}