#include "tile.hpp"

Tile::Tile(int id, const SDL_Rect &srcRect, Type type) 
    : Tile(id, srcRect, type, false, false, nullptr)
{}

Tile::Tile(int id, const SDL_Rect &srcRect, Type type, bool givesCoins, bool givesCandy, Property *property)
    : id(id), srcRect(srcRect), type(type), givesCoins(givesCoins), givesCandy(givesCandy), property(property)
{}

Tile::Tile(const Tile &tile)
    : Tile(tile.id, tile.srcRect, tile.type, tile.doesGiveCoins(), tile.doesGiveCandy(), tile.property)
{}

Tile::~Tile()
{
    setProperty(nullptr);
}

int Tile::getId() const
{
    return id;
}

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

void Tile::setProperty(Property *property)
{
    if(this->property)
    {
        delete this->property;
    }
    this->property = property;
}

void Tile::step(MapSprite *sprite) const
{
    if(property)
    {
        property->onStep(sprite);
    }
}
