#ifndef _OPEN_TOT_TILE_HPP_
#define _OPEN_TOT_TILE_HPP_

#include "util/const.hpp"

enum TileType
{
    GROUND = 1,
    IMPASSABLE = 2,
    WATER = 3,
    FLYABLE = 4
};

struct Tile
{
    TileType type;
    int x;
    int y;
};

#endif