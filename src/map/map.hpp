#ifndef _OPEN_TOT_MAP_HPP_
#define _OPEN_TOT_MAP_HPP_

#include "tileset.hpp"

class PlayerSprite;

class Map
{
public:
    Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, Tileset *tileset);
    ~Map();

    void update(unsigned int deltaTime);
    void draw(const Window &window);

    PlayerSprite * getPlayer() const;

private:
    void loadMapValues(json *mapJson);
    void loadTileGrid(json *mapJson);

    Tileset *tileset;
    SDL_Texture *mapTexture;
    std::vector<std::vector<unsigned int>> tileGrid;
    int mapTileWidth;
    int mapTileHeight;
    int cameraWidth;
    int cameraHeight;
    PlayerSprite *player;
};

#endif
