#ifndef _OPEN_TOT_TILE_HPP_
#define _OPEN_TOT_TILE_HPP_

#include "util/util.hpp"

class Tile
{
public:
    enum Type {GROUND, WATER, OBSTACLE, GATE, SMASHABLE, IMPASSABLE};
    
    Tile(const SDL_Rect &srcRect, Type type, bool givesCoins, bool givesCandy);

    const SDL_Rect & getSourceRect() const;
    void setSourceRect(const SDL_Rect &srcRect);

    Type getType() const;
    void setType(Type type);
    
    bool doesGiveCoins() const;
    void setGivesCoins(bool givesCoins);

    bool doesGiveCandy() const;
    void setGivesCandy(bool givesCandy);

private:
    SDL_Rect srcRect;
    Type type;
    bool givesCoins;
    bool givesCandy;
};

#endif
