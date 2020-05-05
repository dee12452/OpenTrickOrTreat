#include "vampiresprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"
#include "objectsprite.hpp"

const SDL_Rect VampireSprite::VAMPIRE_INITIAL_SRC = {0, 0, 48, 48};
const unsigned short int VampireSprite::VAMPIRE_NUM_WALKING_ANIMATIONS = 8;
const int VampireSprite::VAMPIRE_HITBOX_Y_OFFSET = 8;
const int VampireSprite::VAMPIRE_HITBOX_W = 30;
const int VampireSprite::VAMPIRE_HITBOX_H = 30;
const unsigned int VampireSprite::VAMPIRE_FLAP_ANIMATION_DURATION = 150;
const unsigned short int VampireSprite::VAMPIRE_BAT_ANIMATION_INDEX = 9;

VampireSprite::VampireSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_VAMPIRE),
        VAMPIRE_INITIAL_SRC,
        VAMPIRE_INITIAL_SRC,
        VAMPIRE_NUM_WALKING_ANIMATIONS)
    , flying(false)
    , vampireFlapDeltaTime(0)
{}

void VampireSprite::update(unsigned int deltaTime, Map *map)
{
    PlayerSprite::update(deltaTime, map);
    if(flying)
    {
        vampireFlapDeltaTime += deltaTime;
        if(vampireFlapDeltaTime > VAMPIRE_FLAP_ANIMATION_DURATION)
        {
            vampireFlapDeltaTime %= VAMPIRE_FLAP_ANIMATION_DURATION;
        }
        const unsigned short int vampireFlapAnimationIndex = vampireFlapDeltaTime / (VAMPIRE_FLAP_ANIMATION_DURATION / 2);
        setSourceX(VAMPIRE_INITIAL_SRC.w * VAMPIRE_BAT_ANIMATION_INDEX + VAMPIRE_INITIAL_SRC.w * vampireFlapAnimationIndex);
    }
}

void VampireSprite::stop()
{
    if(flying)
    {
        MapSprite::stop();
    }
    else
    {
        PlayerSprite::stop();
    }
    
}

void VampireSprite::doAction(Map *map)
{
    if(flying)
    {
        const SDL_Rect hitbox = getHitbox();
        const std::vector<SDL_Point> corners = 
        {
            {hitbox.x, hitbox.y},
            {hitbox.x + hitbox.w, hitbox.y},
            {hitbox.x, hitbox.y + hitbox.h},
            {hitbox.x + hitbox.w, hitbox.y + hitbox.h}
        };
        for(auto corner : corners)
        {
            Tile *tile = map->findTile(corner.x, corner.y);
            if(!tile || tile->type != TileType::GROUND) return;
        }
        flying = false;
    }
    else
    {
        flying = true;
    }
}

CostumeType VampireSprite::getCostume() const
{
    return VAMPIRE;
}

bool VampireSprite::isFlying() const
{
    return flying;
}

bool VampireSprite::canMove(Map *map, const SDL_Point &pos) const
{
    if(flying)
    {
        Tile *nextTile1 = nullptr;
        Tile *nextTile2 = nullptr;
        ObjectSprite *intersectingObject1 = nullptr;
        ObjectSprite *intersectingObject2 = nullptr;
        const SDL_Rect hitbox = getHitbox();
        findCollisions(map, pos, nextTile1, nextTile2, intersectingObject1, intersectingObject2);
        if(!nextTile1 || !nextTile2)
        {
            return false;
        }
        if(intersectingObject1 && intersectingObject1->isBlocking())
        {
            return false;
        }
        if(intersectingObject2 && intersectingObject2->isBlocking())
        {
            return false;
        }
        if(nextTile1->type != TileType::FLYABLE && nextTile1->type != TileType::GROUND)
        {
            return false;
        }
        if(nextTile2->type != TileType::FLYABLE && nextTile2->type != TileType::GROUND)
        {
            return false;
        }
        return true;
    }
    else
    {
        return PlayerSprite::canMove(map, pos);
    }
}

SDL_Rect VampireSprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - VAMPIRE_HITBOX_W / 2,
        center.y - VAMPIRE_HITBOX_H / 2 + VAMPIRE_HITBOX_Y_OFFSET,
        VAMPIRE_HITBOX_W,
        VAMPIRE_HITBOX_H
    };
}