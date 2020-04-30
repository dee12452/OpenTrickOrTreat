#include "playersprite.hpp"
#include "objectsprite.hpp"
#include "map/map.hpp"

const unsigned int PlayerSprite::WALK_ANIMATION_CYCLE_LENGTH = 500;
const unsigned short int PlayerSprite::WALK_BUFFER_PIXELS = 10;

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

void PlayerSprite::draw(const Window &window) const
{
    const SDL_Rect dstRectCentered = { getX(), getY() - getHeight() / 3, getWidth(), getHeight() };
    window.draw(getSdlTexture(), getSourceRect(), dstRectCentered);
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

bool PlayerSprite::canMove(Map *map, unsigned int x, unsigned int y)
{
    Tile *nextTile1 = nullptr;
    Tile *nextTile2 = nullptr;
    ObjectSprite *intersectingObject1 = nullptr;
    ObjectSprite *intersectingObject2 = nullptr;
    switch (getMoveDirection())
    {
        case Direction::UP:
        {
            const int leftX = x + WALK_BUFFER_PIXELS;
            const int rightX = x + getWidth() - WALK_BUFFER_PIXELS;
            nextTile1 = getTile(map, leftX, y);
            nextTile2 = getTile(map, rightX, y);
            intersectingObject1 = findObject(map, leftX, y);
            intersectingObject2 = findObject(map, rightX, y);
            break;
        }
        case Direction::RIGHT:
        {
            const int topY = y + WALK_BUFFER_PIXELS;
            const int bottomY = y + getHeight() - WALK_BUFFER_PIXELS;
            const int nextX = x + getWidth();
            nextTile1 = getTile(map, nextX, topY);
            nextTile2 = getTile(map, nextX, bottomY);
            intersectingObject1 = findObject(map, nextX, topY);
            intersectingObject2 = findObject(map, nextX, bottomY);
            break;
        }
        case Direction::DOWN:
        {
            const int leftX = x + WALK_BUFFER_PIXELS;
            const int rightX = x + getWidth() - WALK_BUFFER_PIXELS;
            const int nextY = y + getHeight() - WALK_BUFFER_PIXELS;
            nextTile1 = getTile(map, leftX, nextY);
            nextTile2 = getTile(map, rightX, nextY);
            intersectingObject1 = findObject(map, leftX, nextY);
            intersectingObject2 = findObject(map, rightX, nextY);
            break;
        }
        case Direction::LEFT:
        {
            const int topY = y + WALK_BUFFER_PIXELS;
            const int bottomY = y + getHeight() - WALK_BUFFER_PIXELS;
            nextTile1 = getTile(map, x, topY);
            nextTile2 = getTile(map, x, bottomY);
            intersectingObject1 = findObject(map, x, topY);
            intersectingObject2 = findObject(map, x, bottomY);
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