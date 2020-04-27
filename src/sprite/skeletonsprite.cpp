#include "skeletonsprite.hpp"
#include "texturemanager.hpp"
#include "map/tile.hpp"

const SDL_Rect SkeletonSprite::SKELETON_INITIAL_SRC = {0, 0, 48, 48};
const int SkeletonSprite::ANIMATION_SKIP = 48;
const unsigned int SkeletonSprite::ANIMATION_DELAY = 45;
const unsigned int SkeletonSprite::SKELETON_ANIMATIONS = 8;
const unsigned int SkeletonSprite::KEYS_ANIMATION_DURATION = 1500;
const SDL_Rect SkeletonSprite::KEYS_INITIAL_SRC = { 440, 3, 28, 15 };

SkeletonSprite::SkeletonSprite()
    : PlayerSprite(TextureManager::getInstance()->getTexture(
        Const::IMAGE_CHARACTERS_SKELETON), 
        SKELETON_INITIAL_SRC, 
        SKELETON_INITIAL_SRC)
    , animationTimer(ANIMATION_DELAY)
    , keyTimer(KEYS_ANIMATION_DURATION)
    , keysActive(false)
{}

void SkeletonSprite::draw(const Window &window)
{
    if(keysActive)
    {
        SDL_Rect keysRect = KEYS_INITIAL_SRC;
        keysRect.y = getY() + getHeight() / 2 - keysRect.h;
        keysRect.x = getX() + getWidth() + keysRect.w / 5;
        window.draw(getSdlTexture(), KEYS_INITIAL_SRC, keysRect);
        keysRect.x = getX() - keysRect.w - keysRect.w / 5;
        window.draw(getSdlTexture(), KEYS_INITIAL_SRC, keysRect);
    }

    PlayerSprite::draw(window);
}

void SkeletonSprite::update(
    unsigned int deltaTime,
    const std::vector<std::vector<unsigned int>> &tileGrid, 
    Tileset *tileset)
{
    PlayerSprite::update(deltaTime, tileGrid, tileset);

    if(keysActive && keyTimer.check())
    {
        keysActive = false;
    }
}

void SkeletonSprite::doAction()
{
    if(keysActive) return;

    keysActive = true;
    keyTimer.reset();
}

void SkeletonSprite::onStopX(int previousSpeed)
{
    if(previousSpeed > 0)
    {
        setSourceRect(SKELETON_INITIAL_SRC);
        setSourceY(SKELETON_INITIAL_SRC.h * 3);
    }
    else
    {
        setSourceRect(SKELETON_INITIAL_SRC);
        setSourceY(SKELETON_INITIAL_SRC.h);
    }

    animationTimer.reset();
}

void SkeletonSprite::onStopY(int previousSpeed)
{
    if(previousSpeed > 0)
    {
        setSourceRect(SKELETON_INITIAL_SRC);
    }
    else
    {
        setSourceRect(SKELETON_INITIAL_SRC);
        setSourceY(SKELETON_INITIAL_SRC.h * 2);
    }

    animationTimer.reset();
}

void SkeletonSprite::onMoveX()
{
    if(!animationTimer.check())
    {
        return;
    }

    if(getSpeedX() > 0)
    {
        if(getSourceY() != SKELETON_INITIAL_SRC.h * 3)
        {
            setSourceRect(SKELETON_INITIAL_SRC);
            setSourceY(SKELETON_INITIAL_SRC.h * 3);
        }
        else
        {
            setSourceX(getSourceX() + SKELETON_INITIAL_SRC.w);
        }
    }
    else
    {
        if(getSourceY() != SKELETON_INITIAL_SRC.h)
        {
            setSourceRect(SKELETON_INITIAL_SRC);
            setSourceY(SKELETON_INITIAL_SRC.h);
        }
        else
        {
            setSourceX(getSourceX() + SKELETON_INITIAL_SRC.w);
        }
    }

    if(getSourceX() > SKELETON_INITIAL_SRC.w * SKELETON_ANIMATIONS)
    {
        setSourceX(SKELETON_INITIAL_SRC.w);
    }

    animationTimer.reset();
}

void SkeletonSprite::onMoveY()
{
    if(!animationTimer.check())
    {
        return;
    }

    if(getSpeedY() > 0)
    {
        if(getSourceY() != 0)
        {
            setSourceRect(SKELETON_INITIAL_SRC);
        }
        else
        {
            setSourceX(getSourceX() + SKELETON_INITIAL_SRC.w);
        }
    }
    else
    {
        if(getSourceY() != SKELETON_INITIAL_SRC.h * 2)
        {
            setSourceRect(SKELETON_INITIAL_SRC);
            setSourceY(SKELETON_INITIAL_SRC.h * 2);
        }
        else
        {
            setSourceX(getSourceX() + SKELETON_INITIAL_SRC.w);
        }
    }

    if(getSourceX() > SKELETON_INITIAL_SRC.w * SKELETON_ANIMATIONS)
    {
        setSourceX(SKELETON_INITIAL_SRC.w);
    }

    animationTimer.reset();
}

bool SkeletonSprite::canMove(
    const std::vector<std::vector<unsigned int>> &tileGrid, 
    Tileset *tileset)
{
    const int buffer = Const::DEFAULT_PLAYER_SPEED * 4;
    switch (getCurrentMoveDirection())
    {
    case MoveDirection::UP:
    {
        const int leftX = getX() + buffer;
        const int rightX = getX() + getWidth() - buffer;
        const int nextY = getY() + getSpeedY();
        const Tile *leftTile = getTile(tileGrid, tileset, leftX, nextY);
        const Tile *rightTile = getTile(tileGrid, tileset, rightX, nextY);
        if(!leftTile || !rightTile) return false;
        return leftTile->type == TileType::GROUND && rightTile->type == TileType::GROUND;
    }
    case MoveDirection::RIGHT:
    {
        const int topY = getY() + buffer;
        const int bottomY = getY() + getHeight() - buffer;
        const int nextX = getX() + getWidth() + getSpeedX();
        const Tile *topTile = getTile(tileGrid, tileset, nextX, topY);
        const Tile *bottomTile = getTile(tileGrid, tileset, nextX, bottomY);
        if(!topTile || !bottomTile) return false;
        return topTile->type == TileType::GROUND && bottomTile->type == TileType::GROUND;
    }
    case MoveDirection::DOWN:
    {
        const int leftX = getX() + buffer;
        const int rightX = getX() + getWidth() - buffer;
        const int nextY = getY() + getHeight() + getSpeedY() - buffer;
        const Tile *leftTile = getTile(tileGrid, tileset, leftX, nextY);
        const Tile *rightTile = getTile(tileGrid, tileset, rightX, nextY);
        if(!leftTile || !rightTile) return false;
        return leftTile->type == TileType::GROUND && rightTile->type == TileType::GROUND;
    }
    case MoveDirection::LEFT:
    {
        const int topY = getY() + buffer;
        const int bottomY = getY() + getHeight() - buffer;
        const int nextX = getX() + getSpeedX();
        const Tile *topTile = getTile(tileGrid, tileset, nextX, topY);
        const Tile *bottomTile = getTile(tileGrid, tileset, nextX, bottomY);
        if(!topTile || !bottomTile) return false;
        return topTile->type == TileType::GROUND && bottomTile->type == TileType::GROUND;
    }
    default:
        break;
    }
    return PlayerSprite::canMove(tileGrid, tileset);
}