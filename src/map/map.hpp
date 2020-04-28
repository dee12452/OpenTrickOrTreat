#ifndef _OPEN_TOT_MAP_HPP_
#define _OPEN_TOT_MAP_HPP_

#include "tileset.hpp"

class PlayerSprite;
class MapSprite;

class Map
{
public:
    Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, Tileset *tileset);
    ~Map();

    void update(unsigned int deltaTime);
    void draw(const Window &window);

    Tileset * getTileset() const;
    PlayerSprite * getPlayer() const;
    std::vector<std::vector<unsigned int>> & getGrid();

    void setRefresh();

private:
    Tileset *tileset;
    SDL_Texture *bgTexture;
    SDL_Texture *mapTexture;
    std::vector<std::vector<unsigned int>> grid;
    int cameraWidth;
    int cameraHeight;
    PlayerSprite *player;
    bool refresh;
    std::vector<MapSprite *> objects;

    void loadMapValues(json *mapJson);
    void loadGrid(json *mapJson, int mapTileWidth, int mapTileHeight);
    void refreshBackground(const Window &window) const;
};

#endif
