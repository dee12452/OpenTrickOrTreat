#include "playersprite.hpp"

const unsigned int PlayerSprite::ANIMATION_TIMER_DELAY = 75;
const unsigned int PlayerSprite::POWER_TIMER_DELAY = 1000;

PlayerSprite::PlayerSprite(SDL_Texture *texture)
    : MapSprite(texture)
    , animationTimer(ANIMATION_TIMER_DELAY)
    , powerTimer(POWER_TIMER_DELAY)
    , upAnimation(nullptr)
    , downAnimation(nullptr)
    , leftAnimation(nullptr)
    , rightAnimation(nullptr)
    , currentCostumeType(CostumeType::NO_COSTUME)
    , usingPower(false)
{
    // Initialize as a skeleton to start
    const SDL_Rect nextAnimRect = changeCostume(CostumeType::SKELETON);
    setSourceRect(nextAnimRect);
    setDestinationRect(nextAnimRect);
}

PlayerSprite::~PlayerSprite()
{
    clearAnimations();
}

void PlayerSprite::stop()
{
    MapSprite::stop();
    Animation * directionAnimation = getDirectionAnimation();
    directionAnimation->reset();
    setSourceRect(directionAnimation->getNext());
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
    changeCostume(type);
}

void PlayerSprite::usePower(Map *map)
{
    switch(currentCostumeType)
    {
        case SKELETON:
        {
            openGates(map);
            break;
        }
        default:
            usingPower = false;
            return;
    }
    stop();
    usingPower = true;
    powerTimer.reset();
}

void PlayerSprite::onUpdate(Map * /*map*/)
{
    animate();
}

void PlayerSprite::onChangeDirection(MoveDirection /*oldState*/, MoveDirection newState)
{
    if(newState == MoveDirection::UP)
    {
        upAnimation->reset();
    }
    else if(newState == MoveDirection::DOWN)
    {
        downAnimation->reset();
    }
    else if(newState == MoveDirection::LEFT)
    {
        leftAnimation->reset();
    }
    else if(newState == MoveDirection::RIGHT)
    {
        rightAnimation->reset();
    }
}

bool PlayerSprite::canMove(Map *map) const
{
    return MapSprite::canMove(map) && !usingPower;
}

void PlayerSprite::animate()
{
    if(!animationTimer.check())
    {
        return;
    }

    if(usingPower)
    {
        // TODO: Do power animation
        if(powerTimer.check())
        {
            usingPower = false;
        }
        else
        {
            return;
        }
    }

    if(!leftAnimation || !rightAnimation || !upAnimation || !downAnimation)
    {
        Util::criticalError("Player animations not loaded properly for costume %d", static_cast<int> (currentCostumeType));
    }

    setSourceRect(getDirectionAnimation()->getNext());
    animationTimer.reset();
}

const SDL_Rect PlayerSprite::changeCostume(CostumeType costumeType)
{
    if(currentCostumeType == costumeType)
    {
        return Const::EMPTY_RECT;
    }

    currentCostumeType = costumeType;
    clearAnimations();
    
    switch(currentCostumeType)
    {
        case CostumeType::SKELETON:
            upAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_UP);
            downAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_DOWN);
            leftAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_LEFT);
            rightAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_RIGHT);
            break;
        case CostumeType::WITCH:
            upAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_WITCH_MV_UP);
            downAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_WITCH_MV_DOWN);
            leftAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_WITCH_MV_LEFT);
            rightAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_WITCH_MV_RIGHT);
            break;
        case CostumeType::MONSTER:
            upAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_MONSTER_MV_UP);
            downAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_MONSTER_MV_DOWN);
            leftAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_MONSTER_MV_LEFT);
            rightAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_MONSTER_MV_RIGHT);
            break;
        case CostumeType::VAMPIRE:
            upAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_VAMPIRE_MV_UP);
            downAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_VAMPIRE_MV_DOWN);
            leftAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_VAMPIRE_MV_LEFT);
            rightAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_VAMPIRE_MV_RIGHT);
            break;
        case CostumeType::FISH:
            upAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_FISH_MV_UP);
            downAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_FISH_MV_DOWN);
            leftAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_FISH_MV_LEFT);
            rightAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_FISH_MV_RIGHT);
            break;
        default:
            upAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_UP);
            downAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_DOWN);
            leftAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_LEFT);
            rightAnimation = AnimationManager::getInstance()->getNewAnimation(Const::ANIMATION_SKELETON_MV_RIGHT);
            break;
    }

    Animation *newAnimationDirection = getDirectionAnimation();
    const SDL_Rect nextAnim = newAnimationDirection->getNext();
    newAnimationDirection->reset();
    return nextAnim;
}

Animation * PlayerSprite::getDirectionAnimation() const
{
    switch(getCurrentDirection())
    {
        case MoveDirection::UP:
            return upAnimation;
        case MoveDirection::DOWN:
            return downAnimation;
        case MoveDirection::LEFT:
            return leftAnimation;
        case MoveDirection::RIGHT:
            return rightAnimation;
    }
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

void PlayerSprite::clearAnimations()
{
    if(upAnimation)
        delete upAnimation;
    if(downAnimation)
        delete downAnimation;
    if(leftAnimation)
        delete leftAnimation;
    if(rightAnimation)
        delete rightAnimation;
    upAnimation = nullptr;
    downAnimation = nullptr;
    leftAnimation = nullptr;
    rightAnimation = nullptr;
}
