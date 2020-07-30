#include "mapsprite.hpp"
#include <algorithm>
#include "objectsprite.hpp"
#include "map/map.hpp"

MapSprite::MapSprite(SDL_Texture *texture)
    : MapSprite(texture, Const::EMPTY_RECT, Const::EMPTY_RECT)
{}

MapSprite::MapSprite(
    SDL_Texture *texture, 
    const SDL_Rect &sourceRect, 
    const SDL_Rect &destinationRect)
    : MapSprite(texture, sourceRect, destinationRect, NONE)
{}

MapSprite::MapSprite(
    SDL_Texture *texture, 
    const SDL_Rect &sourceRect,
    const SDL_Rect &destinationRect,
    Direction facingDir)
    : Sprite(texture, sourceRect, destinationRect)
    , offsetX(0)
    , offsetY(0)
    , speedX(0)
    , speedY(0)
    , facingDirection(facingDir)
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

SDL_Rect MapSprite::getHitbox() const
{
    return getDestinationRect();
}

bool MapSprite::isColliding(MapSprite *otherSprite) const
{
    const SDL_Rect thisHitbox = getHitbox(), thatHitbox = otherSprite->getHitbox();
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