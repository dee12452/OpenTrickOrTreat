#include "creaturesprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"

const SDL_Rect CreatureSprite::CREATURE_INITIAL_SRC = {0, 0, 56, 56};
const unsigned short int CreatureSprite::CREATURE_WALK_ANIMATIONS = 8;
const int CreatureSprite::CREATURE_HITBOX_Y_OFFSET = 12;
const int CreatureSprite::CREATURE_HITBOX_W = 30;
const int CreatureSprite::CREATURE_HITBOX_H = 30;
const unsigned int CreatureSprite::CREATURE_JUMP_ANIMATION_DURATION = 450;
const unsigned short int CreatureSprite::CREATURE_JUMP_NUM_ANIMATIONS = 4;
const unsigned int CreatureSprite::CREATURE_SPLASH_ANIMATION_DURATION = 450;
const std::vector<SDL_Rect> CreatureSprite::CREATURE_SPASH_ANIMATION_SOURCES =
{
    {600, 13, 35, 26},
    {592, 38, 51, 31},
    {582, 75, 71, 33},
    {584, 112, 73, 33},
    {584, 150, 74, 37},
    {592, 194, 61, 28},
    {591, 227, 64, 50},
    {592, 280, 60, 53},
    {596, 342, 54, 38},
    {604, 387, 40, 26}
};

const unsigned short int CreatureSprite::CREATURE_SWIM_NUM_ANIMATIONS = 4;
const unsigned int CreatureSprite::SWIM_ANIMATION_CYCLE_DURATION = 400;

CreatureSprite::CreatureSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_CREATURE),
        CREATURE_INITIAL_SRC,
        CREATURE_INITIAL_SRC,
        CREATURE_WALK_ANIMATIONS,
        CREATURE_INITIAL_SRC.h)
    , jumping(false)
    , swimming(false)
    , jumpingAnimationDelta(0)
    , splashAnimationDelta(0)
    , jumpingPoint({})
    , swimDeltaTime(0)
{}

void CreatureSprite::update(unsigned int deltaTime, Map *map)
{
    if(jumping)
    {
        if(!swimming)
        {
            if(jumpingAnimationDelta < CREATURE_JUMP_ANIMATION_DURATION)
            {
                jumpingAnimationDelta += deltaTime;
                const unsigned short int jumpingAnimationNum = jumpingAnimationDelta / (CREATURE_JUMP_ANIMATION_DURATION / CREATURE_JUMP_NUM_ANIMATIONS);
                setSourceX(CREATURE_INITIAL_SRC.w * jumpingAnimationNum);
                switch (getFacingDirection())
                {
                    case UP:
                        setY(jumpingPoint.y - getHeight() / 2 - (map->getTileset()->getTileHeight() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    case DOWN:
                        setY(jumpingPoint.y - getHeight() / 2 + (map->getTileset()->getTileHeight() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    case LEFT:
                        setX(jumpingPoint.x - getWidth() / 2 - (map->getTileset()->getTileWidth() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    case RIGHT:
                        setX(jumpingPoint.x  - getWidth() / 2 + (map->getTileset()->getTileWidth() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    default:
                        break;
                }
                if(jumpingAnimationDelta >= CREATURE_JUMP_ANIMATION_DURATION)
                {
                    switch (getFacingDirection())
                    {
                        case UP:
                            setY(jumpingPoint.y - getHeight() / 2 - map->getTileset()->getTileHeight());
                            break;
                        case DOWN:
                            setY(jumpingPoint.y - getHeight() / 2 + map->getTileset()->getTileHeight());
                            break;
                        case LEFT:
                            setX(jumpingPoint.x - getWidth() / 2 - map->getTileset()->getTileWidth());
                            break;
                        case RIGHT:
                            setX(jumpingPoint.x - getWidth() / 2 + map->getTileset()->getTileWidth());
                            break;
                        default:
                            break;
                    }
                    setSourceRect(CREATURE_SPASH_ANIMATION_SOURCES.front());
                    const SDL_Point center = getCenter();
                    setWidth(getSourceWidth());
                    setHeight(getSourceHeight());
                    setX(center.x - getWidth() / 2);
                    setY(center.y - getHeight() / 2);
                }
            }
            else if(splashAnimationDelta < CREATURE_SPLASH_ANIMATION_DURATION)
            {
                splashAnimationDelta += deltaTime;
                const unsigned short int splashAnimationNum = splashAnimationDelta / 
                    (CREATURE_SPLASH_ANIMATION_DURATION / CREATURE_SPASH_ANIMATION_SOURCES.size());
                setSourceRect(CREATURE_SPASH_ANIMATION_SOURCES[
                    std::min(splashAnimationNum, static_cast<unsigned short int> (CREATURE_SPASH_ANIMATION_SOURCES.size() - 1))]);
                const SDL_Point center = getCenter();
                setWidth(getSourceWidth());
                setHeight(getSourceHeight());
                setX(center.x - getWidth() / 2);
                setY(center.y - getHeight() / 2);
            }
            else
            {
                jumping = false;
                swimming = true;
                jumpingAnimationDelta = 0;
                splashAnimationDelta = 0;
                setSourceRect(CREATURE_INITIAL_SRC);
                setSourceX(getSourceWidth() * (CREATURE_JUMP_NUM_ANIMATIONS + 1));
                switch (getFacingDirection())
                {
                    case UP:
                        setSourceY(getSourceHeight() * 5);
                        break;
                    case DOWN:
                        setSourceY(getSourceHeight());
                        break;
                    case LEFT:
                        setSourceY(getSourceHeight() * 3);
                        break;
                    case RIGHT:
                        setSourceY(getSourceHeight() * 7);
                        break;
                    default:
                        break;
                }
                const SDL_Point center = getCenter();
                setWidth(getSourceWidth());
                setHeight(getSourceHeight());
                setX(center.x - getWidth() / 2);
                setY(center.y - getHeight() / 2);
            }
        }
        else
        {
            if(jumpingAnimationDelta < CREATURE_JUMP_ANIMATION_DURATION)
            {
                jumpingAnimationDelta += deltaTime;
                const unsigned short int jumpingAnimationNum = jumpingAnimationDelta / (CREATURE_JUMP_ANIMATION_DURATION / CREATURE_JUMP_NUM_ANIMATIONS);
                setSourceX(CREATURE_INITIAL_SRC.w * (CREATURE_JUMP_NUM_ANIMATIONS - jumpingAnimationNum));
                switch (getFacingDirection())
                {
                    case UP:
                        setY(jumpingPoint.y - getHeight() / 2 - (map->getTileset()->getTileHeight() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    case DOWN:
                        setY(jumpingPoint.y - getHeight() / 2 + (map->getTileset()->getTileHeight() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    case LEFT:
                        setX(jumpingPoint.x - getWidth() / 2 - (map->getTileset()->getTileWidth() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    case RIGHT:
                        setX(jumpingPoint.x  - getWidth() / 2 + (map->getTileset()->getTileWidth() * jumpingAnimationDelta) / CREATURE_JUMP_ANIMATION_DURATION);
                        break;
                    default:
                        break;
                }
                if(jumpingAnimationDelta >= CREATURE_JUMP_ANIMATION_DURATION)
                {
                    setSourceRect(CREATURE_INITIAL_SRC);
                    switch (getFacingDirection())
                    {
                        case UP:
                            setY(jumpingPoint.y - getHeight() / 2 - map->getTileset()->getTileHeight());
                            setSourceY((CREATURE_INITIAL_SRC.h + CREATURE_INITIAL_SRC.h) * 2);
                            break;
                        case DOWN:
                            setY(jumpingPoint.y - getHeight() / 2 + map->getTileset()->getTileHeight());
                            break;
                        case LEFT:
                            setX(jumpingPoint.x - getWidth() / 2 - map->getTileset()->getTileWidth());
                            setSourceY(CREATURE_INITIAL_SRC.h + CREATURE_INITIAL_SRC.h);
                            break;
                        case RIGHT:
                            setX(jumpingPoint.x - getWidth() / 2 + map->getTileset()->getTileWidth());
                            setSourceY((CREATURE_INITIAL_SRC.h + CREATURE_INITIAL_SRC.h) * 3);
                            break;
                        default:
                            break;
                    }
                    jumping = false;
                    swimming = false;
                    jumpingAnimationDelta = 0;
                }
            }
        }
        
    }
    else
    {
        PlayerSprite::update(deltaTime, map);
        if(swimming)
        {
            swimDeltaTime += deltaTime;
        }
    }
}

void CreatureSprite::doAction(Map *map)
{
    if(jumping) return;
    
    const SDL_Point center = getCenter();
    Tile *facingTile = nullptr;
    switch(getFacingDirection())
    {
        case UP:
            facingTile = map->findTile(center.x, center.y - map->getTileset()->getTileHeight());
            break;
        case DOWN:
            facingTile = map->findTile(center.x, center.y + map->getTileset()->getTileHeight());
            break;
        case LEFT:
            facingTile = map->findTile(center.x - map->getTileset()->getTileWidth(), center.y);
            break;
        case RIGHT:
            facingTile = map->findTile(center.x + map->getTileset()->getTileWidth(), center.y);
            break;
        default:
            break;
    }
    if(!facingTile) return;

    if(swimming && facingTile->type == TileType::GROUND) jumping = true;
    else if(!swimming && facingTile->type == TileType::WATER) jumping = true;

    if(jumping)
    {
        jumpingPoint = getCenter();
        if(!swimming)
        {
            setSourceY(getSourceY() + getSourceHeight());
        }
        else
        {
            setSourceX(getSourceWidth() * (CREATURE_SWIM_NUM_ANIMATIONS - 1));
        }
    }
}

void CreatureSprite::stop()
{
    if(jumping) return;

    if(swimming)
    {
        PlayerSprite::stop();
        setSourceX(getSourceWidth() * (CREATURE_JUMP_NUM_ANIMATIONS + 1));
    }
    else PlayerSprite::stop();
}

CostumeType CreatureSprite::getCostume() const
{
    return CREATURE;
}

void CreatureSprite::onMoveX()
{
    if(jumping) return;

    if(swimming)
    {
        unsigned int currentAnimationIndex = swimDeltaTime / (SWIM_ANIMATION_CYCLE_DURATION / CREATURE_SWIM_NUM_ANIMATIONS);
        if(currentAnimationIndex >= CREATURE_SWIM_NUM_ANIMATIONS)
        {
            currentAnimationIndex = 0;
            swimDeltaTime = 0;
            setSourceX(getSourceWidth() * (CREATURE_JUMP_NUM_ANIMATIONS + 1));
        }

        if(getSpeedX() > 0)
        {
            setSourceY(CREATURE_INITIAL_SRC.h * 7);
            setSourceX(getSourceWidth() * (currentAnimationIndex + CREATURE_JUMP_NUM_ANIMATIONS));
        }
        else
        {
            setSourceY(CREATURE_INITIAL_SRC.h * 3);
            setSourceX(getSourceWidth() * (currentAnimationIndex + CREATURE_JUMP_NUM_ANIMATIONS));
        }
    }
    else
    {
        PlayerSprite::onMoveX();
    }
}

void CreatureSprite::onMoveY()
{
    if(jumping) return;

    if(swimming)
    {
        unsigned int currentAnimationIndex = swimDeltaTime / (SWIM_ANIMATION_CYCLE_DURATION / CREATURE_SWIM_NUM_ANIMATIONS);
        if(currentAnimationIndex >= CREATURE_SWIM_NUM_ANIMATIONS)
        {
            currentAnimationIndex = 0;
            swimDeltaTime = 0;
            setSourceX(getSourceWidth() * CREATURE_JUMP_NUM_ANIMATIONS);
        }

        if(getSpeedY() > 0)
        {
            setSourceY(CREATURE_INITIAL_SRC.h);
            setSourceX(getSourceWidth() * (currentAnimationIndex + CREATURE_JUMP_NUM_ANIMATIONS));
        }
        else
        {
            setSourceY(CREATURE_INITIAL_SRC.h * 5);
            setSourceX(getSourceWidth() * (currentAnimationIndex + CREATURE_JUMP_NUM_ANIMATIONS));
        }
    }
    else
    {
        PlayerSprite::onMoveY();
    }
}

bool CreatureSprite::canMove(Map *map, int x, int y) const
{
    if(jumping) return false;

    if(swimming)
    {
        Tile *nextTile1 = nullptr;
        Tile *nextTile2 = nullptr;
        const SDL_Rect hitbox = getHitbox();
        switch (getMoveDirection())
        {
            case Direction::UP:
            {
                const int leftX = hitbox.x;
                const int rightX = hitbox.x + hitbox.w;
                const int nextY = hitbox.y - (getY() - y);
                nextTile1 = map->findTile(leftX, nextY);
                nextTile2 = map->findTile(rightX, nextY);
                break;
            }
            case Direction::RIGHT:
            {
                const int topY = hitbox.y;
                const int bottomY = hitbox.y + hitbox.h;
                const int nextX = hitbox.x + hitbox.w + x - getX();
                nextTile1 = map->findTile(nextX, topY);
                nextTile2 = map->findTile(nextX, bottomY);
                break;
            }
            case Direction::DOWN:
            {
                const int leftX = hitbox.x;
                const int rightX = hitbox.x + hitbox.w;
                const int nextY = hitbox.y + hitbox.h + y - getY();
                nextTile1 = map->findTile(leftX, nextY);
                nextTile2 = map->findTile(rightX, nextY);
                break;
            }
            case Direction::LEFT:
            {
                const int topY = hitbox.y;
                const int bottomY = hitbox.y + hitbox.h;
                const int nextX = hitbox.x - (getX() - x);
                nextTile1 = map->findTile(nextX, topY);
                nextTile2 = map->findTile(nextX, bottomY);
                break;
            }
            default:
                return true;
        }
        if(nextTile1 && nextTile2 && nextTile1->type == TileType::WATER && nextTile2->type == TileType::WATER)
        {
            return true;
        }
        return false;
    }
    else
    {
        return PlayerSprite::canMove(map, x, y);   
    }
}

SDL_Rect CreatureSprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - CREATURE_HITBOX_W / 2,
        center.y - CREATURE_HITBOX_H / 2 + CREATURE_HITBOX_Y_OFFSET,
        CREATURE_HITBOX_W,
        CREATURE_HITBOX_H
    };
}