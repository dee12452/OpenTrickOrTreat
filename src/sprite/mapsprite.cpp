#include "mapsprite.hpp"
#include <algorithm>
#include "objectsprite.hpp"
#include "map/map.hpp"

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
    const unsigned int nextX = getX() + static_cast<int> (offsetX + speedX * deltaTime);
    const unsigned int nextY = getY() + static_cast<int> (offsetY + speedY * deltaTime);
    if(canMove(map, nextX, nextY))
    {
        offsetX += speedX * deltaTime;
        offsetY += speedY * deltaTime;
        setX(nextX);
        setY(nextY);
        float whole;
        offsetX = modf(offsetX, &whole);
        offsetY = modf(offsetY, &whole);
    }
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

bool MapSprite::canMove(Map *, unsigned int, unsigned int)
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

Tile * MapSprite::getTile(Map *map, int x, int y) const
{
    const int tileX = x / map->getTileset()->getTileWidth();
    const int tileY = y / map->getTileset()->getTileHeight();
    if(tileY < 0 || tileY >= map->getGrid().size())
    {
        return nullptr;
    }
    if(tileX < 0 || tileX >= map->getGrid()[tileY].size())
    {
        return nullptr;
    }
    return map->getTileset()->getTile(map->getGrid()[tileY][tileX]);
}

ObjectSprite * MapSprite::findObject(Map *map, int x, int y) const
{
    for(auto object : map->getObjects())
    {
        if(object->getX() <= x && object->getX() + object->getWidth() >= x)
        {
            if(object->getY() <= y && object->getY() + object->getHeight() >= y)
            {
                return object;
            }
        }
    }
    return nullptr;
}

float MapSprite::getOffsetX() const
{
    return offsetX;
}

float MapSprite::getOffsetY() const
{
    return offsetY;
}