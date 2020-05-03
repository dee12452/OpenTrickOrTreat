#include "breakablesprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"

const unsigned int BreakableSprite::BOULDER_SRC_TILE_ID = 8;
const unsigned int BreakableSprite::TRASH_CAN_SRC_TILE_ID = 29;
const unsigned int BreakableSprite::BREAK_ANIMATION_DURATION = 750;
const unsigned int BreakableSprite::BREAK_ANIMATION_UP_DURATION = 250;
const unsigned int BreakableSprite::BREAK_ANIMATION_SRC_W = 8;
const unsigned int BreakableSprite::BREAK_ANIMATION_SRC_H = 8;
const unsigned short int BreakableSprite::BREAK_ANIMATION_NUM_PIECES = 10;

BreakableSprite::BreakableSprite(Tileset *tileset, BreakableType type, const SDL_Point &mapPos)
    : ObjectSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_TILESET),
        Const::EMPTY_RECT,
        Const::EMPTY_RECT)
    , breakableType(type)
    , broken(false)
    , breakAnimationDelta(0)
{
    Tile *srcTile = nullptr;
    switch (breakableType)
    {
        case BOULDER:
            srcTile = tileset->getTile(BOULDER_SRC_TILE_ID);
            break;
        default:
            srcTile = tileset->getTile(TRASH_CAN_SRC_TILE_ID);
            break;
    }
    setSourceRect({srcTile->x, srcTile->y, tileset->getTileWidth(), tileset->getTileHeight()});
    setDestinationRect(getSourceRect());
    setX(mapPos.x - mapPos.x % tileset->getTileWidth());
    setY(mapPos.y - mapPos.y % tileset->getTileHeight());
    breakAnimationSrc.w = BREAK_ANIMATION_SRC_W;
    breakAnimationSrc.h = BREAK_ANIMATION_SRC_H;
    breakAnimationSrc.x = getSourceX() + getSourceWidth() / 2 - breakAnimationSrc.w / 2;
    breakAnimationSrc.y = getSourceY() + getSourceHeight() / 2 - breakAnimationSrc.h / 2;
}

void BreakableSprite::update(unsigned int deltaTime, Map *map)
{
    if(!broken) return;
    if(breakAnimationDelta + deltaTime >= BREAK_ANIMATION_DURATION)
    {
        if(!brokenPiecesDst.empty()) brokenPiecesDst.clear();
        return;
    }
    breakAnimationDelta += deltaTime;
    int nextY;
    if(breakAnimationDelta <= BREAK_ANIMATION_UP_DURATION)
    {
        nextY = getY() - (static_cast<float> (getY()) * 
            (static_cast<float> (breakAnimationDelta) / static_cast<float> (BREAK_ANIMATION_UP_DURATION))); 
    }
    else
    {
        nextY = getY() + (static_cast<float> (getY()) * 
            (static_cast<float> (breakAnimationDelta - BREAK_ANIMATION_UP_DURATION) / static_cast<float> (BREAK_ANIMATION_DURATION - BREAK_ANIMATION_UP_DURATION))); 
    }
    brokenPiecesDst.clear();
    for(int piece = 0; piece < BREAK_ANIMATION_NUM_PIECES; piece++)
    {
        int nextX;
        if(piece < BREAK_ANIMATION_NUM_PIECES / 2)
        {
            nextX = getX() - piece * BREAK_ANIMATION_SRC_W * BREAK_ANIMATION_SRC_W * 
                (static_cast<float> (breakAnimationDelta) / static_cast<float> (BREAK_ANIMATION_DURATION));
        }
        else if(piece > BREAK_ANIMATION_NUM_PIECES / 2)
        {
            nextX = getX() + piece * BREAK_ANIMATION_SRC_W * BREAK_ANIMATION_SRC_W * 
                (static_cast<float> (breakAnimationDelta) / static_cast<float> (BREAK_ANIMATION_DURATION));
        }
        else
        {
            nextX = getX();
        }
        brokenPiecesDst.push_back({nextX, nextY, BREAK_ANIMATION_SRC_W, BREAK_ANIMATION_SRC_H});
    }
}

void BreakableSprite::draw(const Window &window) const
{
    if(!broken)
    {
        ObjectSprite::draw(window);
    }
    else
    {
        for(auto pieceDst : brokenPiecesDst)
        {
            window.draw(getSdlTexture(), breakAnimationSrc, pieceDst);
        }
    }
    
}

ObjectType BreakableSprite::getType() const
{
    return BREAKABLE;
}

bool BreakableSprite::isBlocking() const
{
    return !broken;
}

void BreakableSprite::breakObject()
{
    broken = true;
}