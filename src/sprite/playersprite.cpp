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

bool PlayerSprite::canMove(Map *map, int x, int y)
{
    Tile *nextTile1 = nullptr;
    Tile *nextTile2 = nullptr;
    ObjectSprite *intersectingObject1 = nullptr;
    ObjectSprite *intersectingObject2 = nullptr;
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
            intersectingObject1 = map->findObject(leftX, nextY);
            intersectingObject2 = map->findObject(rightX, nextY);
            break;
        }
        case Direction::RIGHT:
        {
            const int topY = hitbox.y;
            const int bottomY = hitbox.y + hitbox.h;
            const int nextX = hitbox.x + hitbox.w + x - getX();
            nextTile1 = map->findTile(nextX, topY);
            nextTile2 = map->findTile(nextX, bottomY);
            intersectingObject1 = map->findObject(nextX, topY);
            intersectingObject2 = map->findObject(nextX, bottomY);
            break;
        }
        case Direction::DOWN:
        {
            const int leftX = hitbox.x;
            const int rightX = hitbox.x + hitbox.w;
            const int nextY = hitbox.y + hitbox.h + y - getY();
            nextTile1 = map->findTile(leftX, nextY);
            nextTile2 = map->findTile(rightX, nextY);
            intersectingObject1 = map->findObject(leftX, nextY);
            intersectingObject2 = map->findObject(rightX, nextY);
            break;
        }
        case Direction::LEFT:
        {
            const int topY = hitbox.y;
            const int bottomY = hitbox.y + hitbox.h;
            const int nextX = hitbox.x - (getX() - x);
            nextTile1 = map->findTile(nextX, topY);
            nextTile2 = map->findTile(nextX, bottomY);
            intersectingObject1 = map->findObject(nextX, topY);
            intersectingObject2 = map->findObject(nextX, bottomY);
            break;
        }
        default:
            return true;
    }
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