#include "tile.hpp"

Tile::Tile(const SDL_Rect &srcRect, Type type, bool givesCoins, bool givesCandy)
    : srcRect(srcRect), type(type), givesCoins(givesCoins), givesCandy(givesCandy)
{}

const SDL_Rect & Tile::getSourceRect() const
{
    return srcRect;
}

void Tile::setSourceRect(const SDL_Rect &srcRect)
{
    this->srcRect = srcRect;
}

Tile::Type Tile::getType() const
{
    return type;
}

void Tile::setType(Tile::Type type)
{
    this->type = type;
}

bool Tile::doesGiveCoins() const
{
    return givesCoins;
}

void Tile::setGivesCoins(bool givesCoins)
{
    this->givesCoins = givesCoins;
}

bool Tile::doesGiveCandy() const
{
    return givesCandy;
}

void Tile::setGivesCandy(bool givesCandy)
{
    this->givesCandy = givesCandy;
}
