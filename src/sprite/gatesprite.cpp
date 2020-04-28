#include "gatesprite.hpp"
#include "map/tileset.hpp"

const unsigned int GateSprite::WOOD_GATE_TILE_ID = 48;
const unsigned int GateSprite::STEEL_GATE_TILE_ID = 5;

GateSprite::GateSprite(Tileset *tileset, GateType type, int x, int y)
    : MapSprite(
        tileset->getTilesetTexture(),
        {0, 0, tileset->getTileWidth(), tileset->getTileHeight()},
        {0, 0, tileset->getTileWidth(), tileset->getTileHeight()})
{
    setX(x - x % tileset->getTileWidth());
    setY(y - y % tileset->getTileHeight());
    switch (type)
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

void GateSprite::update(unsigned int deltaTime, Map *map)
{
    MapSprite::update(deltaTime, map);
}

void GateSprite::unlock()
{
    unlocked = true;
}

bool GateSprite::isOpen() const
{
    return false;
}