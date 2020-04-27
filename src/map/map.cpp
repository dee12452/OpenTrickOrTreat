#include "map.hpp"
#include "GahoodSON/parse.h"
#include "sprite/skeletonsprite.hpp"

Map::Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, Tileset *ts)
    : tileset(ts)
{
    player = new SkeletonSprite();
    const std::string mapPath = pathToResourceFolder + Const::MAPS_FOLDER_PATH + mapFile;
    json *mapJson = gahoodson_create_from_file(mapPath.c_str());
    loadMapValues(mapJson);
    loadTileGrid(mapJson);
    gahoodson_delete(mapJson);
    const int mapTextureWidth = mapTileWidth * tileset->getTileWidth();
    const int mapTextureHeight = mapTileHeight * tileset->getTileHeight();
    mapTexture = window.createTexture(mapTextureWidth, mapTextureHeight);
}

Map::~Map()
{
    if(mapTexture)
    {
        SDL_DestroyTexture(mapTexture);
    }
    if(player)
    {
        delete player;
    }
    tileset = nullptr;
}

void Map::update(unsigned int deltaTime)
{
    player->update(deltaTime, tileGrid, tileset);
}

void Map::draw(const Window &window)
{
    window.setTargetTexture(mapTexture);
    window.clear();
    for(int y = 0; y < tileGrid.size(); y++)
    {
        for(int x = 0; x < tileGrid[y].size(); x++)
        {
            const unsigned int tileId = tileGrid[y][x];
            const Tile *tile = tileset->getTile(tileId);
            if(!tile)
            {
                continue;
            }

            const SDL_Rect dstRect = { 
                x * tileset->getTileWidth(), 
                y * tileset->getTileHeight(), 
                tileset->getTileWidth(), 
                tileset->getTileHeight() 
            };
            window.draw(tileset->getTilesetTexture(), tile->location, dstRect);
        }
    }
    player->draw(window);
    window.resetTargetTexture();

    const int cameraWidthPixels = cameraWidth * tileset->getTileWidth();
    const int cameraHeightPixels = cameraHeight * tileset->getTileHeight();
    const SDL_Rect mapSrc = { 
        player->getX() + player->getWidth() / 2 - cameraWidthPixels / 2, 
        player->getY() + player->getHeight() / 2 - cameraHeightPixels / 2, 
        cameraWidthPixels, 
        cameraHeightPixels 
    };
    window.draw(mapTexture, mapSrc);
}

PlayerSprite * Map::getPlayer() const
{
    return player;
}

void Map::loadMapValues(json *mapJson)
{
    mapTileWidth = Util::getJsonPair("width", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    mapTileHeight = Util::getJsonPair("height", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    cameraWidth = 0;
    cameraHeight = 0;
    json_list *properties = Util::getJsonList("properties", mapJson->json_lists, mapJson->num_of_lists);
    for(int elementIndex = 0; elementIndex < properties->num_of_elements; elementIndex++)
    {
        json_list_element *element = properties->elements[elementIndex];
        const std::string propertyName = Util::getJsonPair("name", element->json_pairs, element->num_of_pairs)->str_val->val;
        if(propertyName == "camerawidth")
        {
            cameraWidth = Util::getJsonPair("value", element->json_pairs, element->num_of_pairs)->int_val->val;
        }
        else if(propertyName == "cameraheight")
        {
            cameraHeight = Util::getJsonPair("value", element->json_pairs, element->num_of_pairs)->int_val->val;
        }
        else if(propertyName == "startx")
        {
            player->setX(Util::getJsonPair(
                "value", 
                element->json_pairs, element->num_of_pairs)->int_val->val * tileset->getTileWidth());
        }
        else if(propertyName == "starty")
        {
            player->setY(Util::getJsonPair(
                "value", 
                element->json_pairs, element->num_of_pairs)->int_val->val * tileset->getTileHeight());
        }
    }
}

void Map::loadTileGrid(json *mapJson)
{
    json_list *layers = Util::getJsonList("layers", mapJson->json_lists, mapJson->num_of_lists);
    json_list *layerData = Util::getJsonList("data", layers->elements[0]->json_lists, layers->elements[0]->num_of_lists);
    int currentElement = 0;
    for(int row = 0; row < mapTileHeight; row++)
    {
        std::vector<unsigned int> currentRow;
        for(int column = 0; column < mapTileWidth; column++)
        {
            currentRow.push_back(layerData->elements[currentElement]->int_val->val);
            currentElement++;
        }
        tileGrid.push_back(currentRow);
    }
}
