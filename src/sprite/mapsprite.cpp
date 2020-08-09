#include "mapsprite.hpp"
#include <algorithm>
#include "objectsprite.hpp"
#include "map/map.hpp"

MapSprite::MapSprite(
    SDL_Texture *texture
    , const SDL_Rect &sourceRect
    , const SDL_Rect &destinationRect)
    : MapSprite(
        texture
        , sourceRect
        , destinationRect
        , NONE)
{}

MapSprite::MapSprite(
    SDL_Texture *texture
    , const SDL_Rect &sourceRect
    , const SDL_Rect &destinationRect
    , Direction facingDirection)
    : MapSprite(
        texture
        , sourceRect
        , destinationRect
        , facingDirection
        , destinationRect
        , Const::EMPTY_RECT)
{}

MapSprite::MapSprite(
    SDL_Texture *texture
    , const SDL_Rect &sourceRect
    , const SDL_Rect &destinationRect
    , Direction facingDirection
    , const Hitbox &collisionHitbox
    , const Hitbox &blockingHitbox)
    : Sprite(texture, sourceRect, destinationRect)
    , offsetX(0)
    , offsetY(0)
    , speedX(0)
    , speedY(0)
    , facingDirection(facingDirection)
    , collisionHitbox(collisionHitbox)
    , blockingHitbox(blockingHitbox)
{}

MapSprite::~MapSprite()
{}

void MapSprite::update(unsigned int deltaTime, Map *map)
{
    const int nextX = getX() + static_cast<int> (offsetX + speedX * deltaTime);
    const int nextY = getY() + static_cast<int> (offsetY + speedY * deltaTime);
    if(speedX != 0)
    {
        if(speedX > 0) facingDirection = RIGHT;
        if(speedX < 0) facingDirection = LEFT;
        onMoveX();
    }
    if(speedY != 0)
    {
        if(speedY > 0) facingDirection = DOWN;
        if(speedY < 0) facingDirection = UP;
        onMoveY();
    }
    if(canMove(map, {nextX, nextY}))
    {
        offsetX += speedX * deltaTime;
        offsetY += speedY * deltaTime;
        setX(nextX);
        setY(nextY);
        float whole;
        offsetX = modf(offsetX, &whole);
        offsetY = modf(offsetY, &whole);
    }
}

void MapSprite::stop()
{
    speedX = 0;
    speedY = 0;
    offsetX = 0;
    offsetY = 0;
}

float MapSprite::getSpeedX() const
{
    return speedX;
}

void MapSprite::setSpeedX(float sX)
{
    speedX = sX;
    if(sX == 0) offsetX = 0;
}

float MapSprite::getSpeedY() const
{
    return speedY;
}

void MapSprite::setSpeedY(float sY)
{
    speedY = sY;
    if(sY == 0) offsetY = 0;
}

bool MapSprite::canMove(Map *, const SDL_Point &) const
{
    return true;
}

void MapSprite::onMoveX()
{}

void MapSprite::onMoveY()
{}

Direction MapSprite::getMoveDirection() const
{
    if(speedX < 0) return Direction::LEFT;
    else if(speedX > 0) return Direction::RIGHT;
    else if(speedY < 0) return Direction::UP;
    else if(speedY > 0) return Direction::DOWN;
    else return Direction::NONE;
}

Direction MapSprite::getFacingDirection() const
{
    return facingDirection;
}

void MapSprite::setFacingDirection(Direction direction)
{
    facingDirection = direction;
}

float MapSprite::getOffsetX() const
{
    return offsetX;
}

float MapSprite::getOffsetY() const
{
    return offsetY;
}

SDL_Point MapSprite::getCenter() const
{
    return {getX() + getWidth() / 2, getY() + getHeight() / 2};
}

const Hitbox & MapSprite::getBlockingHitbox() const
{
    return blockingHitbox;
}

void MapSprite::setBlockingHitbox(const Hitbox &hitbox)
{
    blockingHitbox = hitbox;
}

const Hitbox & MapSprite::getCollisionHitbox() const
{
    return collisionHitbox;
}

void MapSprite::setCollisionHitbox(const Hitbox &hitbox)
{
    collisionHitbox = hitbox;
}

bool MapSprite::isColliding(MapSprite *otherSprite) const
{
    return isColliding({otherSprite->getX(), otherSprite->getY()}, otherSprite->getCollisionHitbox());
}

bool MapSprite::isColliding(const SDL_Point &otherMapLoc, const Hitbox &otherHitbox) const
{
    return checkHitboxCollision({getX(), getY()}, collisionHitbox, otherMapLoc, otherHitbox);
}

SDL_Rect MapSprite::getHitboxRect(const Hitbox &hitbox) const
{
    const SDL_Point center = getCenter();
    return {center.x - hitbox.width / 2, center.y - hitbox.height / 2, hitbox.width, hitbox.height};
}

bool MapSprite::checkHitboxCollision(const SDL_Point &mapLoc1, const Hitbox &hitbox1, const SDL_Point &mapLoc2, const Hitbox &hitbox2) const
{
    const SDL_Rect thisHitbox = {mapLoc1.x, mapLoc1.y, hitbox1.width, hitbox1.height};
    const SDL_Rect thatHitbox = {mapLoc2.x, mapLoc2.y, hitbox2.width, hitbox2.height};
    if(thisHitbox.x <= thatHitbox.x && thisHitbox.x + thisHitbox.w >= thatHitbox.x)
    {
        if(thisHitbox.y <= thatHitbox.y && thisHitbox.y + thisHitbox.h >= thatHitbox.y)
        {
            return true;
        }
        else if(thisHitbox.y >= thatHitbox.y && thisHitbox.y <= thatHitbox.y + thatHitbox.h)
        {
            return true;
        }
    }
    else if(thisHitbox.x >= thatHitbox.x && thisHitbox.x <= thatHitbox.x + thatHitbox.w)
    {
        if(thisHitbox.y <= thatHitbox.y && thisHitbox.y + thisHitbox.h >= thatHitbox.y)
        {
            return true;
        }
        else if(thisHitbox.y >= thatHitbox.y && thisHitbox.y <= thatHitbox.y + thatHitbox.h)
        {
            return true;
        }
    }
    return false;
}