#include "gatesprite.hpp"
#include "map/map.hpp"

const unsigned int GateSprite::WOOD_GATE_TILE_ID = 48;
const unsigned int GateSprite::STEEL_GATE_TILE_ID = 5;
const std::vector<unsigned int> GateSprite::WOOD_GATE_ANIMATION_TILES = {70, 48, 70, 71, 72, 73, 25};
const std::vector<unsigned int> GateSprite::STEEL_GATE_ANIMATION_TILES = {27, 5, 27, 28, 50, 51, 25};
const unsigned int GateSprite::GATE_ANIMATION_DURATION = 900;

GateSprite::GateSprite(Tileset *tileset, GateType type, int x, int y)
    : ObjectSprite(
        tileset->getTilesetTexture(),
        {0, 0, tileset->getTileWidth(), tileset->getTileHeight()},
        {0, 0, tileset->getTileWidth(), tileset->getTileHeight()})
    , gateType(type)
    , currentAnimationDelta(0)
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
        gateAnimationTiles = WOOD_GATE_ANIMATION_TILES;
        break;
    default:
        setSourceX(tileset->getTile(STEEL_GATE_TILE_ID)->x);
        setSourceY(tileset->getTile(STEEL_GATE_TILE_ID)->y);
        gateAnimationTiles = STEEL_GATE_ANIMATION_TILES;
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
    default:
        return ObjectType::STEEL_GATE;
    }
}

bool GateSprite::isBlocking() const
{
    return !open;
}

void GateSprite::update(unsigned int deltaTime, Map *map)
{
    if(!open && unlocked)
    {
        currentAnimationDelta += deltaTime;
        const unsigned int animationLength = GATE_ANIMATION_DURATION / gateAnimationTiles.size();
        unsigned int animationIndex = currentAnimationDelta / animationLength;
        if(animationIndex >= gateAnimationTiles.size()) animationIndex = gateAnimationTiles.size() - 1;
        setSourceX(map->getTileset()->getTile(gateAnimationTiles[animationIndex])->x);
        setSourceY(map->getTileset()->getTile(gateAnimationTiles[animationIndex])->y);
        if(animationIndex == gateAnimationTiles.size() - 1)
        {
            open = true;
        }
    }
}

void GateSprite::unlock()
{
    unlocked = true;
    currentAnimationDelta = 0;
}