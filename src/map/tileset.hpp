#ifndef _OPEN_TOT_TILESET_HPP_
#define _OPEN_TOT_TILESET_HPP_

#include "texturemanager.hpp"

enum TileType
{
    GROUND
};

struct Tile
{
    TileType type;
    SDL_Rect location;
};

class Tileset
{
public:
    Tileset(const std::string &pathToResourceFolder);
    ~Tileset();

    SDL_Texture * getTilesetTexture() const;
    Tile * getTile(unsigned int tileNumber) const;
    int getTileWidth() const;
    int getTileHeight() const;

private:
    SDL_Texture *tilesetTexture;
    std::vector<Tile *> tiles;
    int tileWidth;
    int tileHeight;
};

#endif
