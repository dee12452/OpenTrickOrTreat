#include "playersprite.hpp"
#include "objectsprite.hpp"
#include "map/map.hpp"

const unsigned int PlayerSprite::WALK_ANIMATION_CYCLE_LENGTH = 500;

PlayerSprite::PlayerSprite(
    SDL_Texture *texture,
    const SDL_Rect &sourceRect,
    const SDL_Rect &destinationRect,
    unsigned short int walkAnimations)
    : PlayerSprite(texture, sourceRect, destinationRect, walkAnimations, 0)
{}

PlayerSprite::PlayerSprite(
    SDL_Texture *texture,
    const SDL_Rect &sourceRect,
    const SDL_Rect &destinationRect,
    unsigned short int walkAnimations,
    unsigned int height)
    : MapSprite(texture, sourceRect, destinationRect, DOWN)
    , initialSource(sourceRect)
    , numWalkAnimations(walkAnimations)
    , walkDeltaTime(0)
    , walking(false)
    , walkDirectionAnimationHeight(height)
    , flying(false)
{}

PlayerSprite::~PlayerSprite()
{}

void PlayerSprite::update(unsigned int deltaTime, Map *map)
{
    MapSprite::update(deltaTime, map);
    if(walking) walkDeltaTime += deltaTime;
    else walkDeltaTime = 0;
}

void PlayerSprite::stop()
{
    MapSprite::stop();
    walking = false;
    setSourceX(0);
}

void PlayerSprite::setFacingDirection(Direction direction)
{
    MapSprite::setFacingDirection(direction);
    switch (direction)
    {
        case UP:
            setSourceY((initialSource.h + walkDirectionAnimationHeight) * 2);
            break;
        case RIGHT:
            setSourceY((initialSource.h +  + walkDirectionAnimationHeight) * 3);
            break;
        case DOWN:
            setSourceY(0);
            break;
        case LEFT:
            setSourceY(initialSource.h + walkDirectionAnimationHeight);
            break;
        default:
            break;
    }
}

bool PlayerSprite::isFlying() const
{
    return flying;
}

void PlayerSprite::onMoveX()
{
    walking = true;

    unsigned int currentAnimationIndex = walkDeltaTime / (WALK_ANIMATION_CYCLE_LENGTH / numWalkAnimations);
    if(currentAnimationIndex >= numWalkAnimations)
    {
        currentAnimationIndex = 0;
        walkDeltaTime = 0;
        setSourceX(0);
    }

    if(getSpeedX() > 0)
    {
        setSourceY((initialSource.h +  + walkDirectionAnimationHeight) * 3);
        setSourceX(initialSource.w * currentAnimationIndex);
    }
    else
    {
        setSourceY(initialSource.h + walkDirectionAnimationHeight);
        setSourceX(initialSource.w * currentAnimationIndex);
    }
}

void PlayerSprite::onMoveY()
{
    walking = true;
    
    unsigned int currentAnimationIndex = walkDeltaTime / (WALK_ANIMATION_CYCLE_LENGTH / numWalkAnimations);
    if(currentAnimationIndex >= numWalkAnimations)
    {
        currentAnimationIndex = 0;
        walkDeltaTime = 0;
        setSourceX(0);
    }

    if(getSpeedY() > 0)
    {
        setSourceY(0);
        setSourceX(initialSource.w * currentAnimationIndex);
    }
    else
    {
        setSourceY((initialSource.h + walkDirectionAnimationHeight) * 2);
        setSourceX(initialSource.w * currentAnimationIndex);
    }
}

bool PlayerSprite::canMove(Map *map, const SDL_Point &pos) const
{
    Tile *nextTile1 = nullptr;
    Tile *nextTile2 = nullptr;
    ObjectSprite *intersectingObject1 = nullptr;
    ObjectSprite *intersectingObject2 = nullptr;
    findCollisions(map, pos, nextTile1, nextTile2, intersectingObject1, intersectingObject2);
    if(!nextTile1 || !nextTile2 || nextTile1->type != TileType::GROUND || nextTile2->type != TileType::GROUND)
    {
        return false;
    }
    if(intersectingObject1 && intersectingObject1->isBlocking())
    {
        return false;
    }
    if(intersectingObject2 && intersectingObject2->isBlocking())
    {
        return false;
    }
    return true;
}

void PlayerSprite::findCollisions(
    Map *map, 
    const SDL_Point &pos, 
    Tile * &tile1, 
    Tile * &tile2, 
    ObjectSprite * &obj1, 
    ObjectSprite * &obj2) const
{
    const SDL_Rect hitbox = getHitbox();
    switch (getFacingDirection())
    {
        case Direction::UP:
        {
            const int leftX = hitbox.x;
            const int rightX = hitbox.x + hitbox.w;
            const int nextY = hitbox.y - (getY() - pos.y);
            tile1 = map->findTile(leftX, nextY);
            tile2 = map->findTile(rightX, nextY);
            obj1 = map->findObject(leftX, nextY);
            obj2 = map->findObject(rightX, nextY);
            break;
        }
        case Direction::RIGHT:
        {
            const int topY = hitbox.y;
            const int bottomY = hitbox.y + hitbox.h;
            const int nextX = hitbox.x + hitbox.w + pos.x - getX();
            tile1 = map->findTile(nextX, topY);
            tile2 = map->findTile(nextX, bottomY);
            obj1 = map->findObject(nextX, topY);
            obj2 = map->findObject(nextX, bottomY);
            break;
        }
        case Direction::DOWN:
        {
            const int leftX = hitbox.x;
            const int rightX = hitbox.x + hitbox.w;
            const int nextY = hitbox.y + hitbox.h + pos.y - getY();
            tile1 = map->findTile(leftX, nextY);
            tile2 = map->findTile(rightX, nextY);
            obj1 = map->findObject(leftX, nextY);
            obj2 = map->findObject(rightX, nextY);
            break;
        }
        case Direction::LEFT:
        {
            const int topY = hitbox.y;
            const int bottomY = hitbox.y + hitbox.h;
            const int nextX = hitbox.x - (getX() - pos.x);
            tile1 = map->findTile(nextX, topY);
            tile2 = map->findTile(nextX, bottomY);
            obj1 = map->findObject(nextX, topY);
            obj2 = map->findObject(nextX, bottomY);
            break;
        }
        default:
            break;
    }
}