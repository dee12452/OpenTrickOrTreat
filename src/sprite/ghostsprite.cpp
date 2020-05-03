#include "ghostsprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"
#include "playersprite.hpp"

const SDL_Rect GhostSprite::GHOST_INITIAL_SRC = {205, 314, 40, 47};
const SDL_Rect GhostSprite::GHOST_FROG_INITIAL_SRC = {369, 336, 29, 26};
const unsigned int GhostSprite::GHOST_FROG_ANIMATION_DURATION = 2500;
const unsigned int GhostSprite::GHOST_FROG_ANIMATION_BLINK_DURATION = 500;

GhostSprite::GhostSprite(Tileset *tileset, const std::vector<SDL_Point> &pth, const SDL_Point &mapPos)
    : ObjectSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_MISC),
        GHOST_INITIAL_SRC,
        Const::EMPTY_RECT)
    , path(pth)
    , currentPathIndex(0)
    , movingForward(true)
    , dead(false)
    , deadDeltaTime(0)
{
    setX(mapPos.x - mapPos.x % tileset->getTileWidth());
    setY(mapPos.y - mapPos.y % tileset->getTileHeight());
    setWidth(getSourceWidth());
    setHeight(getSourceHeight());
}

void GhostSprite::update(unsigned int deltaTime, Map *map)
{
    if(dead)
    {
        deadDeltaTime += deltaTime;
        if(deadDeltaTime > GHOST_FROG_ANIMATION_DURATION)
        {
            setSourceX(GHOST_FROG_INITIAL_SRC.x);
            deadDeltaTime = deadDeltaTime % GHOST_FROG_ANIMATION_DURATION;
        }
        else if(deadDeltaTime > GHOST_FROG_ANIMATION_DURATION - GHOST_FROG_ANIMATION_BLINK_DURATION)
        {
            setSourceX(GHOST_FROG_INITIAL_SRC.x + GHOST_FROG_INITIAL_SRC.w);
        }
        return;
    }

    if(currentPathIndex == path.size() - 1)
    {
        movingForward = false;
    }
    if(currentPathIndex == 0)
    {
        movingForward = true;
    }
    SDL_Point nextPoint;
    if(movingForward)
    {
        nextPoint = path[currentPathIndex + 1];
    }
    else
    {
        nextPoint = path[currentPathIndex - 1];
    }
    if(nextPoint.x != path[currentPathIndex].x)
    {
        setSpeedY(0);
        if(nextPoint.x > path[currentPathIndex].x)
        {
            if(getX() > nextPoint.x * map->getTileset()->getTileWidth())
            {
                setX(nextPoint.x * map->getTileset()->getTileWidth());
                currentPathIndex = movingForward ? currentPathIndex + 1 : currentPathIndex - 1;
            }
            else
            {
                setSpeedX(Const::DEFAULT_PLAYER_SPEED);
            }
        }
        else
        {
            if(getX() < nextPoint.x * map->getTileset()->getTileWidth())
            {
                setX(nextPoint.x * map->getTileset()->getTileWidth());
                currentPathIndex = movingForward ? currentPathIndex + 1 : currentPathIndex - 1;
            }
            else
            {
                setSpeedX(-Const::DEFAULT_PLAYER_SPEED);
            }
        }
    }
    else
    {
        setSpeedX(0);
        if(nextPoint.y > path[currentPathIndex].y)
        {
            if(getY() > nextPoint.y * map->getTileset()->getTileHeight())
            {
                setY(nextPoint.y * map->getTileset()->getTileHeight());
                currentPathIndex = movingForward ? currentPathIndex + 1 : currentPathIndex - 1;
            }
            else
            {
                setSpeedY(Const::DEFAULT_PLAYER_SPEED);
            }
        }
        else
        {
            if(getY() < nextPoint.y * map->getTileset()->getTileHeight())
            {
                setY(nextPoint.y * map->getTileset()->getTileHeight());
                currentPathIndex = movingForward ? currentPathIndex + 1 : currentPathIndex - 1;
            }
            else
            {
                setSpeedY(-Const::DEFAULT_PLAYER_SPEED);
            }
        }
    }
    ObjectSprite::update(deltaTime, map);
}

ObjectType GhostSprite::getType() const
{
    return GHOST;
}

bool GhostSprite::isBlocking() const
{
    return !dead;
}

void GhostSprite::kill()
{
    dead = true;
    setSourceRect(GHOST_FROG_INITIAL_SRC);
    const SDL_Point center = getCenter();
    const SDL_Rect newDst = 
    {
        center.x - getSourceWidth() / 2, 
        center.y - getSourceHeight() / 2, 
        getSourceWidth(), 
        getSourceHeight()
    };
    setDestinationRect(newDst);
}

void GhostSprite::onMoveX()
{
    if(getMoveDirection() == RIGHT)
    {
        setSourceX(GHOST_INITIAL_SRC.x + GHOST_INITIAL_SRC.w * 3);
    }
    else
    {
        setSourceX(GHOST_INITIAL_SRC.x + GHOST_INITIAL_SRC.w);
    }
    
}

void GhostSprite::onMoveY()
{
    if(getMoveDirection() == DOWN)
    {
        setSourceX(GHOST_INITIAL_SRC.x);
    }
    else
    {
        setSourceX(GHOST_INITIAL_SRC.x + GHOST_INITIAL_SRC.w * 2);
    }
}

bool GhostSprite::canMove(Map *map, int x, int y) const
{
    return !isColliding(map->getPlayer());
}