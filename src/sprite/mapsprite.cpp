#include "mapsprite.hpp"

MapSprite::MapSprite(SDL_Texture *texture)
    : MapSprite(texture, Const::EMPTY_RECT, Const::EMPTY_RECT)
{}

MapSprite::MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : Sprite(texture, sourceRect, destinationRect)
      , locationX(0)
      , locationY(0)
      , locationZ(0)
      , speedX(0)
      , speedY(0)
      , oldDirection(MoveDirection::DOWN)
      , newDirection(MoveDirection::DOWN)
      , disabled(false)
      , noClip(false)
{}

MapSprite::~MapSprite()
{}

int MapSprite::getLocationX() const
{
    return locationX;
}

void MapSprite::setLocationX(Map *map, int x)
{
    locationX = x;
    clampLocation(map);
}

int MapSprite::getLocationY() const
{
    return locationY;
}

void MapSprite::setLocationY(Map *map, int y)
{
    locationY = y;
    clampLocation(map);
}

unsigned int MapSprite::getLocationZ() const
{
    return locationZ;
}
    
void MapSprite::setLocationZ(unsigned int z)
{
    locationZ = z;
}

unsigned int MapSprite::getMapTileX(Map *map) const
{
    return getLocationX() / map->getTileColumns();
}

unsigned int MapSprite::getMapTileY(Map *map) const
{
    return getLocationY() / map->getTileRows();
}

void MapSprite::update(Map *map)
{
    onUpdate(map);
    if(canMove(map))
    {
        locationX += speedX;
        locationY += speedY;
    }
    clampLocation(map);
    checkDirectionChanges();
}

void MapSprite::draw(const Window &window, Map *currentMap, const SDL_Rect &camera, unsigned int z)
{
    if(getLocationZ() != z)
        return;
    
    const int drawCharacterTileX = getMapTileX(currentMap);
    const int drawCharacterTileY = getMapTileY(currentMap);
    
    if(drawCharacterTileX < camera.x || drawCharacterTileX > camera.x + camera.w)
        return;
    
    if(drawCharacterTileY < camera.y || drawCharacterTileY > camera.y + camera.h)
        return;

    const int cameraTileX = drawCharacterTileX - camera.x;
    const int cameraTileY = drawCharacterTileY - camera.y;
    const int drawOffsetX = (getLocationX() % currentMap->getTileColumns()) - (getWidth() / 2);
    const int drawOffsetY = (getLocationY() % currentMap->getTileRows()) - (getHeight() / 2);
    
    setX((cameraTileX * currentMap->getTilePixelWidth()) + drawOffsetX);
    setY((cameraTileY * currentMap->getTilePixelHeight()) + drawOffsetY);
    Sprite::draw(window);
}

int MapSprite::getSpeedX() const
{
    return speedX;
}

void MapSprite::setSpeedX(int sX)
{
    speedY = 0;
    speedX = sX;
    if(speedX > 0)
    {
        newDirection = MoveDirection::RIGHT;
    }
    else if(speedX < 0)
    {
        newDirection = MoveDirection::LEFT;
    }
}

int MapSprite::getSpeedY() const
{
    return speedY;
}

void MapSprite::setSpeedY(int sY)
{
    speedX = 0;
    speedY = sY;
    if(speedY > 0)
    {
        newDirection = MoveDirection::DOWN;
    }
    else if(speedY < 0)
    {
        newDirection = MoveDirection::UP;
    }
}

void MapSprite::stop()
{
    speedX = 0;
    speedY = 0;
}

bool MapSprite::isDisabled() const
{
    return disabled;
}

void MapSprite::setDisable(bool disabled)
{
    this->disabled = disabled;
}

bool MapSprite::isNoClip() const
{
    return noClip;
}

void MapSprite::toggleNoClip()
{
    noClip = !noClip;
}

void MapSprite::checkCollision(MapSprite *otherSprite)
{
    if(getLocationX() <= otherSprite->getLocationX() && getLocationX() + getWidth() >= otherSprite->getLocationX())
    {
        if(getLocationY() <= otherSprite->getLocationY() && getLocationY() + getHeight() >= otherSprite->getLocationY())
        {
            onCollide(otherSprite);
        }
        else if(getLocationY() >= otherSprite->getLocationY() && getLocationY() <= otherSprite->getLocationY() + otherSprite->getHeight())
        {
            onCollide(otherSprite);
        }
    }
    else if(getLocationX() >= otherSprite->getLocationX() && getLocationX() <= otherSprite->getLocationX() + otherSprite->getWidth())
    {
        if(getLocationY() <= otherSprite->getLocationY() && getLocationY() + getHeight() >= otherSprite->getLocationY())
        {
            onCollide(otherSprite);
        }
        else if(getLocationY() >= otherSprite->getLocationY() && getLocationY() <= otherSprite->getLocationY() + otherSprite->getHeight())
        {
            onCollide(otherSprite);
        }
    }
}

bool MapSprite::isPlayer() const
{
    return false;
}

void MapSprite::onUpdate(Map * /*currentMap*/)
{}

void MapSprite::onChangeDirection(MoveDirection /*oldState*/, MoveDirection /*newState*/)
{}

void MapSprite::onNewTile(const Tile &/*oldTile*/, const Tile &/*newTile*/)
{}

void MapSprite::onCollide(MapSprite * /*other*/)
{}

bool MapSprite::canMove(Map *map) const
{
    if(noClip)
    {
        return true;
    }

    const int nextTileX = (locationX + speedX) / map->getTileColumns();
    const int nextTileY = (locationY + speedY) / map->getTileRows();
    if(nextTileX < 0 || static_cast<unsigned int> (nextTileX) > map->getTileColumns() || 
            nextTileY < 0 || static_cast<unsigned int> (nextTileY) > map->getTileRows())
    {
        return false;
    }
    for(unsigned layerNumber = 0; layerNumber < map->getNumberOfLayers(); layerNumber++)
    {
        const Tile *mapTile = map->getTile(layerNumber, nextTileX, nextTileY);
        if(!mapTile) //Blank tiles are acceptable on higher layers
            continue;

        if(mapTile->getType() != Tile::Type::GROUND)
        {
            return false;
        }
    }
    return true;
}

MoveDirection MapSprite::getCurrentDirection() const
{
    return newDirection;
}

void MapSprite::setCurrentDirection(MoveDirection newDir)
{
    oldDirection = newDirection;
    newDirection = newDir;
}

MoveDirection MapSprite::getOldDirection() const
{
    return oldDirection;
}

void MapSprite::setUnsafeLocationX(int x)
{
    locationX = x;
}

void MapSprite::setUnsafeLocationY(int y)
{
    locationY = y;
}

void MapSprite::checkDirectionChanges()
{
    if(oldDirection == newDirection)
    {
        return;
    }
   
    onChangeDirection(oldDirection, newDirection);
    oldDirection = newDirection;
}

void MapSprite::clampLocation(Map *map)
{
    if(locationX < 0)
    {
        locationX = 0;
    }
    else if(locationX > static_cast<int> (map->getTilePixelWidth() * (map->getTileColumns() + 1)))
    {
        locationX = map->getTilePixelWidth() * (map->getTileColumns() + 1);
    }
    
    if(locationY < 0)
    {
        locationY = 0;
    }
    else if(locationY > static_cast<int> (map->getTilePixelHeight() * (map->getTileRows() + 1)))
    {
        locationY = map->getTilePixelHeight() * (map->getTileRows() + 1);
    }
}
