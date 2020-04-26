#include "map.hpp"
#include "GahoodSON/parse.h"

Map::Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, const Tileset &tileset)
{
    const std::string mapPath = pathToResourceFolder + Const::MAPS_FOLDER_PATH + mapFile;
    json *mapJson = gahoodson_create_from_file(mapPath.c_str());
    loadMapValues(mapJson, tileset.getTileWidth(), tileset.getTileHeight());
    loadTileGrid(mapJson);
    gahoodson_delete(mapJson);
    const int mapTextureWidth = (mapWidth + camera.w / tileset.getTileWidth()) * tileset.getTileWidth();
    const int mapTextureHeight = (mapHeight + camera.h / tileset.getTileHeight()) * tileset.getTileHeight();
    mapTexture = window.createTexture(mapTextureWidth, mapTextureHeight);
}

Map::~Map()
{
    if(mapTexture)
    {
        SDL_DestroyTexture(mapTexture);
        mapTexture = nullptr;
    }
}

void Map::draw(const Window &window, const Tileset &tileset) const
{
    window.setTargetTexture(mapTexture);
    window.clear();
    for(int y = 0; y < tileGrid.size(); y++)
    {
        for(int x = 0; x < tileGrid[y].size(); x++)
        {
            const unsigned int tileId = tileGrid[y][x];
            const Tile *tile = tileset.getTile(tileId);
            if(!tile)
            {
                continue;
            }

            const SDL_Rect dstRect = { 
                camera.w / 2 + x * tileset.getTileWidth(), 
                camera.h / 2 + y * tileset.getTileHeight(), 
                tileset.getTileWidth(), 
                tileset.getTileHeight() 
            };
            window.draw(tileset.getTilesetTexture(), tile->location, dstRect);
        }
    }
    window.resetTargetTexture();
    window.draw(mapTexture, camera);
}

void Map::loadMapValues(json *mapJson, int tileWidth, int tileHeight)
{
    this->mapWidth = Util::getJsonPair("width", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    this->mapHeight = Util::getJsonPair("height", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    this->camera = { 0, 0, 0, 0 };
    json_list *properties = Util::getJsonList("properties", mapJson->json_lists, mapJson->num_of_lists);
    for(int elementIndex = 0; elementIndex < properties->num_of_elements; elementIndex++)
    {
        json_list_element *element = properties->elements[elementIndex];
        const std::string propertyName = Util::getJsonPair("name", element->json_pairs, element->num_of_pairs)->str_val->val;
        if(propertyName == "camerawidth")
        {
            camera.w = Util::getJsonPair("value", element->json_pairs, element->num_of_pairs)->int_val->val * tileWidth;
        }
        else if(propertyName == "cameraheight")
        {
            camera.h = Util::getJsonPair("value", element->json_pairs, element->num_of_pairs)->int_val->val * tileHeight;
        }
        else if(propertyName == "startx")
        {
            camera.x = Util::getJsonPair("value", element->json_pairs, element->num_of_pairs)->int_val->val * tileWidth;
        }
        else if(propertyName == "starty")
        {
            camera.y = Util::getJsonPair("value", element->json_pairs, element->num_of_pairs)->int_val->val * tileHeight;
        }
    }
}

void Map::loadTileGrid(json *mapJson)
{
    json_list *layers = Util::getJsonList("layers", mapJson->json_lists, mapJson->num_of_lists);
    json_list *layerData = Util::getJsonList("data", layers->elements[0]->json_lists, layers->elements[0]->num_of_lists);
    int currentElement = 0;
    for(int row = 0; row < mapHeight; row++)
    {
        std::vector<unsigned int> currentRow;
        for(int column = 0; column < mapWidth; column++)
        {
            currentRow.push_back(layerData->elements[currentElement]->int_val->val);
            currentElement++;
        }
        tileGrid.push_back(currentRow);
    }
}
