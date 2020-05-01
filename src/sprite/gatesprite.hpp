#ifndef _OPEN_TOT_GATE_SPRITE_HPP_
#define _OPEN_TOT_GATE_SPRITE_HPP_

#include "objectsprite.hpp"
#include "util/timer.hpp"

class Tileset;

enum GateType
{
    WOOD = 0,
    STEEL = 1
};

class GateSprite : public ObjectSprite
{
private:
    static const unsigned int WOOD_GATE_TILE_ID;
    static const unsigned int STEEL_GATE_TILE_ID;
    static const std::vector<unsigned int> WOOD_GATE_ANIMATION_TILES;
    static const std::vector<unsigned int> STEEL_GATE_ANIMATION_TILES;
    static const unsigned int GATE_ANIMATION_DURATION;

public:
    GateSprite(Tileset *tileset, GateType type, int x, int y);
    ~GateSprite() override;

    ObjectType getType() const override;
    bool isBlocking() const override;

    void update(unsigned int deltaTime, Map *map) override;
    void unlock();

private:
    GateType gateType;
    unsigned int currentAnimationDelta;
    bool unlocked;
    bool open;
    std::vector<unsigned int> gateAnimationTiles;
};

#endif