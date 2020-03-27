#ifndef _OPEN_TOT_MAP_HPP_
#define _OPEN_TOT_MAP_HPP_

#include "tileset.hpp"

class Map
{
public:
    Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, const Tileset &tileset);
    ~Map();

    void draw(const Window &window, const Tileset &tileset) const;

private:
    void loadMapValues(json *mapJson, int tileWidth, int tileHeight);
    void loadTileGrid(json *mapJson);

    SDL_Texture *mapTexture;
    std::vector<std::vector<unsigned int>> tileGrid;
    int mapWidth;
    int mapHeight;
    SDL_Rect camera;
};

#endif
