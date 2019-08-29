#include "playersprite.hpp"

const unsigned int PlayerSprite::ANIMATION_TIMER_DELAY = 85;

PlayerSprite::PlayerSprite(SDL_Texture *texture)
    : MapSprite(texture)
    , animationTimer(ANIMATION_TIMER_DELAY)
    , upAnimation(AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_UP))
    , downAnimation(AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_DOWN))
    , leftAnimation(AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_LEFT))
    , rightAnimation(AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_RIGHT))
    , currentCostumeType(CostumeType::SKELETON)
{
    setDestinationRect(downAnimation->getNext());
    downAnimation->reset();
    setSourceRect(downAnimation->getNext());
    downAnimation->reset();
}

PlayerSprite::~PlayerSprite()
{
    if(upAnimation)
        delete upAnimation;
    if(downAnimation)
        delete downAnimation;
    if(leftAnimation)
        delete leftAnimation;
    if(rightAnimation)
        delete rightAnimation;
}

bool PlayerSprite::isPlayer() const
{
    return true;
}

CostumeType PlayerSprite::getCostumeType() const
{
    return currentCostumeType;
}

void PlayerSprite::setCostumeType(CostumeType type) 
{
    currentCostumeType = type;
}

void PlayerSprite::doAction(Map *map)
{
    switch(currentCostumeType)
    {
        case SKELETON:
        {
            openGates(map);
            break;
        }
        default:
            break;
    }
}

void PlayerSprite::onUpdate(Map * /*map*/)
{
    animate();
}

void PlayerSprite::onChangeDirectionX(MoveDirectionX /*oldState*/, MoveDirectionX newState)
{
    if(newState == LEFT)
    {
        leftAnimation->reset();
    }
    else if(newState == RIGHT)
    {
        rightAnimation->reset();
    }
}

void PlayerSprite::onChangeDirectionY(MoveDirectionY /*oldState*/, MoveDirectionY newState)
{
    if(newState == UP)
    {
        upAnimation->reset();
    }
    else if(newState == DOWN)
    {
        downAnimation->reset();
    }
}

void PlayerSprite::animate()
{
    if(!animationTimer.check())
    {
        return;
    }

    switch(getCurrentDirectionX())
    {
        case LEFT:
            setSourceRect(leftAnimation->getNext());
            break;
        case RIGHT:
            setSourceRect(rightAnimation->getNext());
            break;
        default:
            break;
    }
    
    switch(getCurrentDirectionY())
    {
        case UP:
            setSourceRect(upAnimation->getNext());
            break;
        case DOWN:
            setSourceRect(downAnimation->getNext());
            break;
        default:
            break;
    }

    animationTimer.reset();
}

void PlayerSprite::onCollide(const MapSprite * /*otherSprite*/)
{
}

void PlayerSprite::openGates(Map *map) const
{
    int tileX = static_cast<int> (getMapTileX(map));
    int tileY = static_cast<int> (getMapTileY(map));
    for(int startTileX = tileX - 1; startTileX <= tileX + 1; startTileX++)
    {
        for(int startTileY = tileY - 1; startTileY <= tileY + 1; startTileY++)
        {
            if(startTileX < 0 
                    || startTileY < 0 
                    || startTileX > static_cast<int> (map->getTileColumns()) 
                    || startTileY > static_cast<int> (map->getTileRows()))
                break;

            for(unsigned int layerNum = 0; layerNum < map->getNumberOfLayers(); layerNum++)
            {
                Tile *directedTile = map->getTile(layerNum, startTileX, startTileY);
                if(directedTile && directedTile->getType() == Tile::Type::GATE)
                {
                    map->removeTile(layerNum, startTileX, startTileY);
                }
            }
        }
    }
}
