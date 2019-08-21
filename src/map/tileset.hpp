#ifndef _OPEN_TOT_TILESET_HPP_
#define _OPEN_TOT_TILESET_HPP_

#include "tile.hpp"

class Tileset
{
public:
    Tileset(const std::string &pathToResourceFolder);
    ~Tileset();

    const std::string & getImageName() const;
    const std::vector<Tile *> & getTiles() const;

private:
    std::string imageName;
    std::vector<Tile *> tiles;
};

#endif
