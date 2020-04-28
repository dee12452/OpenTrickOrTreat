#include "playersprite.hpp"
#include "objectsprite.hpp"
#include "map/map.hpp"

const unsigned int PlayerSprite::WALK_ANIMATION_DELAY = 50;

PlayerSprite::PlayerSprite(
    SDL_Texture *texture,
    const SDL_Rect &sourceRect,
    const SDL_Rect &destinationRect,
    unsigned short int walkAnimations)
    : MapSprite(texture, sourceRect, destinationRect)
    , walkAnimationTimer(WALK_ANIMATION_DELAY)
    , initialSource(sourceRect)
    , numWalkAnimations(walkAnimations)
{}

PlayerSprite::~PlayerSprite()
{}

void PlayerSprite::draw(const Window &window) const
{
    const SDL_Rect dstRectCentered = { getX(), getY() - getHeight() / 3, getWidth(), getHeight() };
    window.draw(getSdlTexture(), getSourceRect(), dstRectCentered);
}

void PlayerSprite::onStopX(int previousSpeed)
{
    if(previousSpeed > 0)
    {
        setSourceRect(initialSource);
        setSourceY(initialSource.h * 3);
    }
    else
    {
        setSourceRect(initialSource);
        setSourceY(initialSource.h);
    }

    walkAnimationTimer.reset();
}

void PlayerSprite::onStopY(int previousSpeed)
{
    if(previousSpeed > 0)
    {
        setSourceRect(initialSource);
    }
    else
    {
        setSourceRect(initialSource);
        setSourceY(initialSource.h * 2);
    }

    walkAnimationTimer.reset();
}

void PlayerSprite::onMoveX()
{
    if(!walkAnimationTimer.check()) return;

    if(getSpeedX() > 0)
    {
        if(getSourceY() != initialSource.h * 3)
        {
            setSourceRect(initialSource);
            setSourceY(initialSource.h * 3);
        }
        else
        {
            setSourceX(getSourceX() + initialSource.w);
        }
    }
    else
    {
        if(getSourceY() != initialSource.h)
        {
            setSourceRect(initialSource);
            setSourceY(initialSource.h);
        }
        else
        {
            setSourceX(getSourceX() + initialSource.w);
        }
    }

    if(getSourceX() > initialSource.w * numWalkAnimations)
    {
        setSourceX(initialSource.w);
    }

    walkAnimationTimer.reset();
}

void PlayerSprite::onMoveY()
{
    if(!walkAnimationTimer.check())
    {
        return;
    }

    if(getSpeedY() > 0)
    {
        if(getSourceY() != 0)
        {
            setSourceRect(initialSource);
        }
        else
        {
            setSourceX(getSourceX() + initialSource.w);
        }
    }
    else
    {
        if(getSourceY() != initialSource.h * 2)
        {
            setSourceRect(initialSource);
            setSourceY(initialSource.h * 2);
        }
        else
        {
            setSourceX(getSourceX() + initialSource.w);
        }
    }

    if(getSourceX() > initialSource.w * numWalkAnimations)
    {
        setSourceX(initialSource.w);
    }

    walkAnimationTimer.reset();
}

bool PlayerSprite::canMove(Map *map)
{
    const int buffer = Const::DEFAULT_PLAYER_SPEED * 4;
    Tile *nextTile1 = nullptr;
    Tile *nextTile2 = nullptr;
    ObjectSprite *intersectingObject1 = nullptr;
    ObjectSprite *intersectingObject2 = nullptr;
    switch (getCurrentMoveDirection())
    {
        case MoveDirection::UP:
        {
            const int leftX = getX() + buffer;
            const int rightX = getX() + getWidth() - buffer;
            const int nextY = getY() + getSpeedY();
            nextTile1 = getTile(map, leftX, nextY);
            nextTile2 = getTile(map, rightX, nextY);
            intersectingObject1 = findObject(map, leftX, nextY);
            intersectingObject2 = findObject(map, rightX, nextY);
            break;
        }
        case MoveDirection::RIGHT:
        {
            const int topY = getY() + buffer;
            const int bottomY = getY() + getHeight() - buffer;
            const int nextX = getX() + getWidth() + getSpeedX();
            nextTile1 = getTile(map, nextX, topY);
            nextTile2 = getTile(map, nextX, bottomY);
            intersectingObject1 = findObject(map, nextX, topY);
            intersectingObject2 = findObject(map, nextX, bottomY);
            break;
        }
        case MoveDirection::DOWN:
        {
            const int leftX = getX() + buffer;
            const int rightX = getX() + getWidth() - buffer;
            const int nextY = getY() + getHeight() + getSpeedY() - buffer;
            nextTile1 = getTile(map, leftX, nextY);
            nextTile2 = getTile(map, rightX, nextY);
            intersectingObject1 = findObject(map, leftX, nextY);
            intersectingObject2 = findObject(map, rightX, nextY);
            break;
        }
        case MoveDirection::LEFT:
        {
            const int topY = getY() + buffer;
            const int bottomY = getY() + getHeight() - buffer;
            const int nextX = getX() + getSpeedX();
            nextTile1 = getTile(map, nextX, topY);
            nextTile2 = getTile(map, nextX, bottomY);
            intersectingObject1 = findObject(map, nextX, topY);
            intersectingObject2 = findObject(map, nextX, bottomY);
            break;
        }
        default:
            return MapSprite::canMove(map);
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