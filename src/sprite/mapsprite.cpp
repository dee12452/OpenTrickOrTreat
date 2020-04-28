#include "mapsprite.hpp"
#include <algorithm>
#include "objectsprite.hpp"
#include "map/map.hpp"

const unsigned int MapSprite::MOVEMENT_DELAY_MS = 35;

MapSprite::MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : Sprite(texture, sourceRect, destinationRect)
    , deltaSpeedTimer(0)
{
    stopX();
    stopY();
}

MapSprite::~MapSprite()
{}

void MapSprite::update(unsigned int deltaTime, Map *map)
{
    deltaSpeedTimer += deltaTime;
    if(deltaSpeedTimer >= MOVEMENT_DELAY_MS)
    {
        if(canMove(map))
        {
            setX(getX() + speedX);
            setY(getY() + speedY);
        }
        if(speedX != 0)
        {
            onMoveX();
        }
        if(speedY != 0)
        {
            onMoveY();
        }
        deltaSpeedTimer = 0;
    }
}

void MapSprite::stopX()
{
    if(speedX != 0)
    {
        onStopX(speedX);
    }
    speedX = 0;
}

void MapSprite::stopY()
{
    if(speedY != 0)
    {
        onStopY(speedY);
    }
    speedY = 0;
}

int MapSprite::getSpeedX() const
{
    return speedX;
}

void MapSprite::setSpeedX(int sX)
{
    speedX = sX;
}

int MapSprite::getSpeedY() const
{
    return speedY;
}

void MapSprite::setSpeedY(int sY)
{
    speedY = sY;
}

void MapSprite::clampX(int minX, int maxX)
{
    setX(std::max(getX() - getWidth() / 2, minX));
    setX(std::min(getX() + getWidth() / 2, maxX));
}

void MapSprite::clampY(int minY, int maxY)
{
    setX(std::max(getY() - getHeight() / 2, minY));
    setX(std::min(getY() + getHeight() / 2, maxY));
}

bool MapSprite::canMove(Map *)
{
    return true;
}

void MapSprite::onStopX(int)
{}

void MapSprite::onStopY(int)
{}

void MapSprite::onMoveX()
{}

void MapSprite::onMoveY()
{}

MoveDirection MapSprite::getCurrentMoveDirection() const
{
    if(speedX < 0) return MoveDirection::LEFT;
    else if(speedX > 0) return MoveDirection::RIGHT;
    else if(speedY < 0) return MoveDirection::UP;
    else if(speedY > 0) return MoveDirection::DOWN;
    else return MoveDirection::NONE;
}

Tile * MapSprite::getTile(Map *map, unsigned int x, unsigned int y) const
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