#include "playersprite.hpp"

const SDL_Rect PlayerSprite::STARTING_SRC = {2, 1, 40, 52};
const unsigned int PlayerSprite::ANIMATION_TIMER_DELAY = 85;

static const SDL_Rect MOTION_DOWN_ANIMATION_SRC_RECTS_DATA[] = {
    {2, 1, 40, 52},
    {42, 1, 40, 52},
    {82, 1, 40, 52},
    {128, 1, 40, 52},
    {170, 1, 40, 52},
    {210, 1, 40, 52},
    {250, 1, 40, 52},
    {290, 1, 40, 52},
};
const SDL_Rect * const PlayerSprite::MOTION_DOWN_ANIMATION_SRC_RECTS = MOTION_DOWN_ANIMATION_SRC_RECTS_DATA;
const unsigned int PlayerSprite::MOTION_DOWN_ANIMATION_SRC_RECTS_SIZE = 8;

const SDL_Rect MOTION_UP_ANIMATION_SRC_RECTS_DATA[] = 
{
    {2, 104, 40, 52},
    {42, 104, 40, 52},
    {84, 104, 40, 52},
    {130, 104, 40, 52},
    {174, 104, 40, 52},
    {214, 104, 40, 52},
    {254, 104, 40, 52},
    {302, 104, 40, 52},
};

const SDL_Rect * const PlayerSprite::MOTION_UP_ANIMATION_SRC_RECTS = MOTION_UP_ANIMATION_SRC_RECTS_DATA;
const unsigned int PlayerSprite::MOTION_UP_ANIMATION_SRC_RECTS_SIZE = 8;

PlayerSprite::PlayerSprite(SDL_Texture *texture)
    : MapSprite(texture, STARTING_SRC, STARTING_SRC)
    , animationTimer(ANIMATION_TIMER_DELAY)
    , currentCostumeType(CostumeType::SKELETON)
    , currentDownAnimIndex(0)
    , currentUpAnimIndex(0)
{}

PlayerSprite::~PlayerSprite()
{}

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
            int tileX = static_cast<int> (getMapTileX(map));
            int tileY = static_cast<int> (getMapTileY(map));
            if(getCurrentDirectionX() == RIGHT) tileX += 1;
            if(getCurrentDirectionX() == LEFT) tileX -= 1;
            if(getCurrentDirectionY() == DOWN) tileY += 1;
            if(getCurrentDirectionY() == UP) tileY -= 1;
            if(tileX < 0 || tileY < 0)
                break;
            for(unsigned int layerNum = 0; layerNum < map->getNumberOfLayers(); layerNum++)
            {
                Tile *directedTile = map->getTile(layerNum, tileX, tileY);
                if(directedTile && directedTile->getType() == Tile::Type::GATE)
                {
                    map->removeTile(layerNum, tileX, tileY);
                }
            }
            break;
        }
        default:
            break;
    }
}

void PlayerSprite::onUpdate(Map * /*currentMap*/)
{
    animate();
}

void PlayerSprite::onChangeDirectionX(MoveDirectionX oldState, MoveDirectionX newState)
{
    if(newState == LEFT)
    {
        setSourceY(STARTING_SRC.h * 1);
    }
    else if(newState == RIGHT)
    {
        setSourceY(STARTING_SRC.h * 3);
    }

    if(newState == NONE_X && (oldState == LEFT || oldState == RIGHT))
    {
        setSourceX(STARTING_SRC.x);
    }
}

void PlayerSprite::onChangeDirectionY(MoveDirectionY oldState, MoveDirectionY newState)
{
    if(newState == UP)
    {
        setSourceY(STARTING_SRC.y + (STARTING_SRC.h * 2));
    }
    else if(newState == DOWN)
    {
        setSourceY(STARTING_SRC.y);
    }

    if(newState == NONE_Y && (oldState == DOWN || oldState == UP))
    {
        setSourceX(STARTING_SRC.x);
    }
    currentUpAnimIndex = 0;
    currentDownAnimIndex = 0;
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
            setSourceX(getSourceX() + STARTING_SRC.w + 1);
            break;
        case RIGHT:
            setSourceX(getSourceX() + STARTING_SRC.w + 1);
            break;
        default:
            break;
    }
    
    switch(getCurrentDirectionY())
    {
        case UP:
            setSourceX(MOTION_UP_ANIMATION_SRC_RECTS[currentUpAnimIndex].x);
            currentUpAnimIndex++;
            if(currentUpAnimIndex >= MOTION_UP_ANIMATION_SRC_RECTS_SIZE) currentUpAnimIndex = 0;
            break;
        case DOWN:
            setSourceX(MOTION_DOWN_ANIMATION_SRC_RECTS[currentDownAnimIndex].x);
            currentDownAnimIndex++;
            if(currentDownAnimIndex >= MOTION_DOWN_ANIMATION_SRC_RECTS_SIZE) currentDownAnimIndex = 0;
            break;
        default:
            break;
    }

    if(getSourceX() > STARTING_SRC.w * 8)
    {
        setSourceX(0);
    }

    animationTimer.reset();
}

void PlayerSprite::onCollide(const MapSprite * /*otherSprite*/)
{
}
