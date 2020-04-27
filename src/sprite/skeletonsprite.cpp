#include "skeletonsprite.hpp"
#include "texturemanager.hpp"
#include "map/tile.hpp"
#include <cmath>

const SDL_Rect SkeletonSprite::SKELETON_INITIAL_SRC = {0, 0, 48, 48};
const int SkeletonSprite::ANIMATION_SKIP = 48;
const unsigned int SkeletonSprite::ANIMATION_DELAY = 45;
const unsigned int SkeletonSprite::SKELETON_ANIMATIONS = 8;
const unsigned int SkeletonSprite::KEYS_ANIMATION_DURATION = 1000;
const SDL_Rect SkeletonSprite::KEY_INITIAL_SRC = { 440, 3, 28, 16 };
const unsigned int SkeletonSprite::KEYS_ANIMATION_DELAY = 35;
const int SkeletonSprite::DEFAULT_KEY_SPEED = 3;
const int SkeletonSprite::KEY_BUFFER = 7;

SkeletonSprite::SkeletonSprite()
    : PlayerSprite(TextureManager::getInstance()->getTexture(
        Const::IMAGE_CHARACTERS_SKELETON), 
        SKELETON_INITIAL_SRC, 
        SKELETON_INITIAL_SRC)
    , animationTimer(ANIMATION_DELAY)
    , keyTimer(KEYS_ANIMATION_DURATION)
    , keyAnimationTimer(KEYS_ANIMATION_DELAY)
    , keysActive(false)
    , keys({
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC), 
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC), 
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC), 
        new MapSprite(getSdlTexture(), KEY_INITIAL_SRC, KEY_INITIAL_SRC)})
{}

SkeletonSprite::~SkeletonSprite()
{
    for(auto &key : keys)
    {
        delete key;
    }
}

void SkeletonSprite::draw(const Window &window) const
{
    if(keysActive)
    {
        for(auto key : keys) key->draw(window);
    }

    PlayerSprite::draw(window);
}

void SkeletonSprite::update(
    unsigned int deltaTime,
    const std::vector<std::vector<unsigned int>> &tileGrid, 
    Tileset *tileset)
{
    PlayerSprite::update(deltaTime, tileGrid, tileset);

    if(keysActive)
    {
        setSourceX(0);
        if(keyTimer.check())
        {
            keysActive = false;
        }
        else if(keyAnimationTimer.check())
        {
            for(auto key : keys) animateKey(key);
            keyAnimationTimer.reset();
        }
        
    }
}

void SkeletonSprite::doAction()
{
    if(keysActive) return;

    keysActive = true;
    keyTimer.reset();
    keyAnimationTimer.reset();
    resetKeys();
}

void SkeletonSprite::onStopX(int previousSpeed)
{
    if(keysActive) return;

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
    if(keysActive) return;

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
    if(!animationTimer.check() || keysActive) return;

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
    if(!animationTimer.check() || keysActive)
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
    if(keysActive)
    {
        return false;
    }

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

void SkeletonSprite::resetKeys() const
{
    for(int keyIndex = 0; keyIndex < keys.size(); keyIndex++)
    {
        Sprite *key = keys[keyIndex];
        key->setSourceRect(KEY_INITIAL_SRC);
        key->setSourceY(key->getSourceHeight() * keyIndex);
        key->setDestinationRect(KEY_INITIAL_SRC);
    }

    const unsigned short int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
    const int circleCenterX = getX() + getWidth() / 2 - keys[UP]->getWidth() / 2;
    const int circleCenterY = getY() + getHeight() / 2 - keys[UP]->getHeight() / 2;
    const int keyRadius = getWidth() - keys[UP]->getWidth() + KEY_BUFFER;

    keys[UP]->setX(circleCenterX);
    keys[UP]->setY(circleCenterY - keyRadius);
    keys[UP]->setSpeedX(DEFAULT_KEY_SPEED);

    keys[RIGHT]->setX(circleCenterX + keyRadius);
    keys[RIGHT]->setY(circleCenterY);
    keys[RIGHT]->setSpeedX(-DEFAULT_KEY_SPEED);

    keys[DOWN]->setX(circleCenterX);
    keys[DOWN]->setY(circleCenterY + keyRadius);
    keys[DOWN]->setSpeedX(-DEFAULT_KEY_SPEED);

    keys[LEFT]->setX(circleCenterX - keyRadius);
    keys[LEFT]->setY(circleCenterY);
    keys[LEFT]->setSpeedX(DEFAULT_KEY_SPEED);
}

void SkeletonSprite::animateKey(MapSprite *key) const
{
    const int circleCenterX = getX() + getWidth() / 2 - key->getWidth() / 2;
    const int circleCenterY = getY() + getHeight() / 2 - key->getHeight() / 2;
    const int keyRadius = getWidth() - key->getWidth() + KEY_BUFFER;
    
    int nextX = key->getX() + key->getSpeedX();
    if(nextX >= circleCenterX + keyRadius)
    {
        nextX = circleCenterX + keyRadius;
        key->setSpeedX(-key->getSpeedX());
    }
    else if(nextX <= circleCenterX - keyRadius)
    {
        nextX = circleCenterX - keyRadius;
        key->setSpeedX(-key->getSpeedX());
    }
    
    const int nextYFactor = static_cast<int> (std::sqrt(std::pow(keyRadius, 2) - std::pow(nextX - circleCenterX, 2)));
    
    if(key->getSpeedX() > 0)
    {
        key->setX(nextX);
        key->setY(circleCenterY + nextYFactor);
    }
    else
    {
        key->setX(nextX);
        key->setY(circleCenterY - nextYFactor);
    }
}