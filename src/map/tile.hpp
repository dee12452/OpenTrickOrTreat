#ifndef _OPEN_TOT_TILE_HPP_
#define _OPEN_TOT_TILE_HPP_

#include "util/const.hpp"

enum TileType
{
    GROUND = 1,
    IMPASSABLE = 2,
    GATE = 3,
    BREAKABLE = 4,
    WATER = 5,
    FLYABLE = 6
};

struct Tile
{
    TileType type;
    SDL_Rect location;
};

#endif