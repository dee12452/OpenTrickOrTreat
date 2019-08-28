#include "playersprite.hpp"

const SDL_Rect PlayerSprite::STARTING_SRC = {2, 1, 40, 52};
const unsigned int PlayerSprite::ANIMATION_TIMER_DELAY = 85;

static const SDL_Rect MOTION_DOWN_ANIMATION_SRC_RECTS_DATA[] = 
{
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

static const SDL_Rect MOTION_UP_ANIMATION_SRC_RECTS_DATA[] = 
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
        setSourceY(STARTING_SRC.h);
    }
    else if(newState == RIGHT)
    {
        setSourceY(STARTING_SRC.h * 3);
    }

    setSourceX(STARTING_SRC.x);
}

void PlayerSprite::onChangeDirectionY(MoveDirectionY /*oldState*/, MoveDirectionY newState)
{
    if(newState == UP)
    {
        setSourceY(STARTING_SRC.y + (STARTING_SRC.h * 2));
    }
    else if(newState == DOWN)
    {
        setSourceY(STARTING_SRC.y);
    }

    setSourceX(STARTING_SRC.x);

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
        setSourceX(STARTING_SRC.x);
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
