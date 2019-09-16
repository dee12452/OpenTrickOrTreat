#ifndef _OPEN_TOT_TILE_HPP_
#define _OPEN_TOT_TILE_HPP_

#include "properties.hpp"
#include "util/util.hpp"

class Tile
{
public:
    enum Type {GROUND, WATER, OBSTACLE, GATE, SMASHABLE, IMPASSABLE};
    
    Tile(int id, const SDL_Rect &srcRect, Type type);
    Tile(int id, const SDL_Rect &srcRect, Type type, bool givesCoins, bool givesCandy, Property *property);
    Tile(const Tile &tile);
    ~Tile();

    int getId() const;

    const SDL_Rect & getSourceRect() const;
    void setSourceRect(const SDL_Rect &srcRect);

    Type getType() const;
    void setType(Type type);
    
    bool doesGiveCoins() const;
    void setGivesCoins(bool givesCoins);

    bool doesGiveCandy() const;
    void setGivesCandy(bool givesCandy);

    void setProperty(Property *property);

    void step(MapSprite *sprite) const;

private:
    int id;
    SDL_Rect srcRect;
    Type type;
    bool givesCoins;
    bool givesCandy;
    Property *property;
};

#endif
