#include "skeletonsprite.hpp"
#include "gatesprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"
#include <cmath>

const SDL_Rect SkeletonSprite::SKELETON_INITIAL_SRC = {0, 0, 48, 48};
const unsigned int SkeletonSprite::SKELETON_ANIMATIONS = 8;
const unsigned int SkeletonSprite::KEYS_ANIMATION_DURATION = 900;
const SDL_Rect SkeletonSprite::KEY_INITIAL_SRC = { 440, 3, 28, 16 };
const unsigned int SkeletonSprite::KEYS_ANIMATION_DELAY = 35;
const unsigned short int SkeletonSprite::DEFAULT_KEY_SPEED = 8;
const int SkeletonSprite::KEY_BUFFER = 7;
const int SkeletonSprite::SKELETON_HITBOX_Y_OFFSET = 8;
const int SkeletonSprite::SKELETON_HITBOX_W = 30;
const int SkeletonSprite::SKELETON_HITBOX_H = 30;

SkeletonSprite::SkeletonSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_SKELETON), 
        SKELETON_INITIAL_SRC, 
        SKELETON_INITIAL_SRC,
        SKELETON_ANIMATIONS)
    , keyDuration(0)
    , keyAnimationDeltaTime(0)
    , keysActive(false)
    , keys({
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC), 
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC), 
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC), 
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC)})
{}

SkeletonSprite::~SkeletonSprite()
{
    for(auto &key : keys)
    {
        delete key;
    }
}

void SkeletonSprite::draw(const Window &window) const
{
    if(keysActive)
    {
        for(auto key : keys) key->draw(window);
    }

    PlayerSprite::draw(window);
}

void SkeletonSprite::update(unsigned int deltaTime, Map *map)
{
    PlayerSprite::update(deltaTime, map);

    if(keysActive)
    {
        keyDuration += deltaTime;
        if(keyDuration > KEYS_ANIMATION_DURATION)
        {
            keysActive = false;
            keyDuration = 0;
            keyAnimationDeltaTime = 0;
        }
        else
        {
            for(auto key : keys) animateKey(key, deltaTime);
        }
        
    }
}

void SkeletonSprite::doAction(Map *map)
{
    if(keysActive) return;

    keysActive = true;
    resetKeys();
    unlockDoors(map);
    setSpeedX(0);
    setSpeedY(0);
    setSourceX(0);
}

CostumeType SkeletonSprite::getCostume() const
{
    return SKELETON;
}

void SkeletonSprite::onMoveX()
{
    if(!keysActive) PlayerSprite::onMoveX();
}

void SkeletonSprite::onMoveY()
{
    if(!keysActive) PlayerSprite::onMoveY();
}

bool SkeletonSprite::canMove(Map *map, const SDL_Point &pos) const
{
    if(keysActive) return false;
    return PlayerSprite::canMove(map, pos);
}

SDL_Rect SkeletonSprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - SKELETON_HITBOX_W / 2,
        center.y - SKELETON_HITBOX_H / 2 + SKELETON_HITBOX_Y_OFFSET,
        SKELETON_HITBOX_W,
        SKELETON_HITBOX_H
    };
}

void SkeletonSprite::resetKeys() const
{
    for(int keyIndex = 0; keyIndex < keys.size(); keyIndex++)
    {
        Sprite *key = keys[keyIndex];
        key->setSourceRect(KEY_INITIAL_SRC);
        key->setSourceY(key->getSourceHeight() * keyIndex);
        key->setDestinationRect(KEY_INITIAL_SRC);
    }

    const unsigned short int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
    const int circleCenterX = getX() + getWidth() / 2 - keys[UP]->getWidth() / 2;
    const int circleCenterY = getY() + getHeight() / 2 - keys[UP]->getHeight() / 2;
    const int keyRadius = getWidth() - keys[UP]->getWidth() + KEY_BUFFER;

    keys[UP]->setX(circleCenterX);
    keys[UP]->setY(circleCenterY - keyRadius);
    keys[UP]->setSpeedX(1);

    keys[RIGHT]->setX(circleCenterX + keyRadius);
    keys[RIGHT]->setY(circleCenterY);
    keys[RIGHT]->setSpeedX(-1);

    keys[DOWN]->setX(circleCenterX);
    keys[DOWN]->setY(circleCenterY + keyRadius);
    keys[DOWN]->setSpeedX(-1);

    keys[LEFT]->setX(circleCenterX - keyRadius);
    keys[LEFT]->setY(circleCenterY);
    keys[LEFT]->setSpeedX(1);
}

void SkeletonSprite::animateKey(MapSprite *key, unsigned int deltaTime)
{
    keyAnimationDeltaTime += deltaTime;
    const int moves = keyAnimationDeltaTime / DEFAULT_KEY_SPEED;
    if(moves == 0)
    {
        return;
    }
    else
    {
        keyAnimationDeltaTime = keyAnimationDeltaTime % moves;
    }
    

    const int circleCenterX = getX() + getWidth() / 2 - key->getWidth() / 2;
    const int circleCenterY = getY() + getHeight() / 2 - key->getHeight() / 2;
    const int keyRadius = getWidth() - key->getWidth() + KEY_BUFFER;
    
    int nextX = key->getX() + key->getSpeedX() * moves;
    if(nextX >= circleCenterX + keyRadius)
    {
        nextX = circleCenterX + keyRadius;
        key->setSpeedX(-key->getSpeedX());
    }
    else if(nextX <= circleCenterX - keyRadius)
    {
        nextX = circleCenterX - keyRadius;
        key->setSpeedX(-key->getSpeedX());
    }
    
    const int nextYFactor = static_cast<int> (std::sqrt(std::pow(keyRadius, 2) - std::pow(nextX - circleCenterX, 2)));
    
    if(key->getSpeedX() > 0)
    {
        key->setX(nextX);
        key->setY(circleCenterY + nextYFactor);
    }
    else
    {
        key->setX(nextX);
        key->setY(circleCenterY - nextYFactor);
    }
}

void SkeletonSprite::unlockDoors(Map *map) const
{
    const int centerX = getX() + getWidth() / 2;
    const int centerY = getY() + getHeight() / 2;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(i == j || -i == j) continue;
            ObjectSprite *obj = map->findObject(
                centerX + (i * map->getTileset()->getTileWidth()),
                centerY + (j * map->getTileset()->getTileHeight()));
            if(obj && obj->getType() == ObjectType::GATE)
            {
                static_cast<GateSprite *> (obj)->unlock();
            }
        }
    }
}