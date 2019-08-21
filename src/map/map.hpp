#ifndef _OPEN_TOT_MAP_HPP_
#define _OPEN_TOT_MAP_HPP_

#include "tileset.hpp"
#include "window.hpp"

struct MapObject
{
    std::string objectType;
    int locationX;
    int locationY;
};

class Map
{
private:
    static const char * const TILE_LAYER_IDENTIFIER;
    static const char * const OBJECT_LAYER_IDENTIFIER;

public:
    Map(const std::string &pathToResourceFolder
            , const std::string &mapFile
            , Tileset *tileset);
    ~Map();

    Tile * getTile(unsigned int layerNumber, int x, int y) const;
    void removeTile(unsigned int layerNumber, int x, int y);
    const std::string & getLevelName() const;
    unsigned int getTimeToComplete() const;
    unsigned int getTileRows() const;
    unsigned int getTileColumns() const;
    int getStartLocationX() const;
    int getStartLocationY() const;
    int getMapPixelWidth() const;
    int getMapPixelHeight() const;
    int getTilePixelWidth() const;
    int getTilePixelHeight() const;
    unsigned int getCameraWidth() const;
    unsigned int getCameraHeight() const;
    unsigned int getNumberOfLayers() const;
    unsigned int getNumberOfMapObjects() const;
    MapObject * getMapObject(unsigned int mapObjectIndex) const;

    void drawLayer(const Window &window
            , unsigned int layerNumber
            , const SDL_Rect &camera
            , SDL_Texture *tilesetTexture);

private:
    std::vector<Tile ***> tileLayers;
    std::vector<MapObject *> mapObjects;
    int startLocationX, startLocationY;
    std::string levelName;
    unsigned int timeToComplete;
    unsigned int tileRows, tileColumns;
    unsigned int tileW, tileH;
    unsigned int cameraWidth, cameraHeight;
};

#endif
