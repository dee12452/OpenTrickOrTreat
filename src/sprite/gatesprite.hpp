#ifndef _OPEN_TOT_GATE_SPRITE_HPP_
#define _OPEN_TOT_GATE_SPRITE_HPP_

#include "mapsprite.hpp"

class Tileset;

enum GateType
{
    WOOD = 0,
    STEEL = 1
};

class GateSprite : public MapSprite
{
private:
    static const unsigned int WOOD_GATE_TILE_ID;
    static const unsigned int STEEL_GATE_TILE_ID;

public:
    GateSprite(Tileset *tileset, GateType type, int x, int y);
    ~GateSprite() override;

    void update(unsigned int deltaTime, Map *map) override;
    void unlock();
    bool isOpen() const;

private:
    bool unlocked;
};

#endif