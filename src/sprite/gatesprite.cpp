#include "gatesprite.hpp"
#include "map/map.hpp"

const unsigned int GateSprite::WOOD_GATE_TILE_ID = 48;
const unsigned int GateSprite::STEEL_GATE_TILE_ID = 5;
const std::vector<unsigned int> GateSprite::WOOD_GATE_ANIMATION_TILES = {70, 48, 70, 71, 72, 73, 25};
const std::vector<unsigned int> GateSprite::STEEL_GATE_ANIMATION_TILES = {27, 5, 27, 28, 50, 51, 25};
const unsigned int GateSprite::ANIMATION_DELAY = 100;

GateSprite::GateSprite(Tileset *tileset, GateType type, int x, int y)
    : ObjectSprite(
        tileset->getTilesetTexture(),
        {0, 0, tileset->getTileWidth(), tileset->getTileHeight()},
        {0, 0, tileset->getTileWidth(), tileset->getTileHeight()})
    , gateType(type)
    , currentAnimation(0)
    , animationTimer(ANIMATION_DELAY)
    , unlocked(false)
    , open(false)
{
    setX(x - x % tileset->getTileWidth());
    setY(y - y % tileset->getTileHeight());
    switch (gateType)
    {
    case GateType::WOOD:
        setSourceX(tileset->getTile(WOOD_GATE_TILE_ID)->x);
        setSourceY(tileset->getTile(WOOD_GATE_TILE_ID)->y);
        break;

    case GateType::STEEL:
        setSourceX(tileset->getTile(STEEL_GATE_TILE_ID)->x);
        setSourceY(tileset->getTile(STEEL_GATE_TILE_ID)->y);
        break;
    }
}

GateSprite::~GateSprite()
{}

ObjectType GateSprite::getType() const
{
    switch (gateType)
    {
    case GateType::WOOD:
        return ObjectType::WOODEN_GATE;
    case GateType::STEEL:
        return ObjectType::STEEL_GATE;
    }
}

bool GateSprite::isBlocking() const
{
    return !open;
}

void GateSprite::update(unsigned int deltaTime, Map *map)
{
    if(!open && unlocked && animationTimer.check())
    {
        unsigned int nextAnimationTile;
        switch(gateType)
        {
            case GateType::WOOD:
                nextAnimationTile = WOOD_GATE_ANIMATION_TILES[currentAnimation];
                break;
            case GateType::STEEL:
                nextAnimationTile = STEEL_GATE_ANIMATION_TILES[currentAnimation];
                break;
        }
        setSourceX(map->getTileset()->getTile(nextAnimationTile)->x);
        setSourceY(map->getTileset()->getTile(nextAnimationTile)->y);
        currentAnimation++;
        switch(gateType)
        {
            case GateType::WOOD:
                open = currentAnimation >= WOOD_GATE_ANIMATION_TILES.size();
                break;
            case GateType::STEEL:
                open = currentAnimation >= STEEL_GATE_ANIMATION_TILES.size();
                break;
        }
        animationTimer.reset();
    }
}

void GateSprite::unlock()
{
    unlocked = true;
}