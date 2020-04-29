#include "map.hpp"
#include "GahoodSON/parse.h"
#include "sprite/skeletonsprite.hpp"
#include "sprite/witchsprite.hpp"
#include "sprite/gatesprite.hpp"

Map::Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, Tileset *ts)
    : tileset(ts), refresh(false)
{
    player = new WitchSprite();
    const std::string mapPath = pathToResourceFolder + Const::MAPS_FOLDER_PATH + mapFile;
    
    json *mapJson = gahoodson_create_from_file(mapPath.c_str());
    const int mapTileWidth = Util::getJsonPair("width", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    const int mapTileHeight = Util::getJsonPair("height", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    loadMapValues(mapJson);
    loadGrid(mapJson, mapTileWidth, mapTileHeight);
    gahoodson_delete(mapJson);

    const int mapTextureWidth = mapTileWidth * tileset->getTileWidth();
    const int mapTextureHeight = mapTileHeight * tileset->getTileHeight();
    bgTexture = window.createTexture(mapTextureWidth, mapTextureHeight);
    mapTexture = window.createTexture(mapTextureWidth, mapTextureHeight);
    refreshBackground(window);
}

Map::~Map()
{
    if(bgTexture)
    {
        SDL_DestroyTexture(bgTexture);
    }
    if(mapTexture)
    {
        SDL_DestroyTexture(mapTexture);
    }
    if(player)
    {
        delete player;
    }
    for(auto &object : objects)
    {
        delete object;
    }
    tileset = nullptr;
}

void Map::update(unsigned int deltaTime)
{
    for(auto object : objects) object->update(deltaTime, this);
    player->update(deltaTime, this);
}

void Map::draw(const Window &window)
{
    if(refresh)
    {
        refreshBackground(window);
        refresh = false;
    }

    window.setTargetTexture(mapTexture);
    window.clear();
    window.drawAll(bgTexture);
    for(auto object : objects) object->draw(window);
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

Tileset * Map::getTileset() const
{
    return tileset;
}

PlayerSprite * Map::getPlayer() const
{
    return player;
}

std::vector<std::vector<unsigned int>> & Map::getGrid()
{
    return grid;
}

const std::vector<ObjectSprite *> & Map::getObjects() const
{
    return objects;
}

void Map::setRefresh()
{
    refresh = true;
}

void Map::loadMapValues(json *mapJson)
{
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

void Map::loadGrid(json *mapJson, int mapTileWidth, int mapTileHeight)
{
    json_list *layers = Util::getJsonList("layers", mapJson->json_lists, mapJson->num_of_lists);
    for(int layer = 0; layer < layers->num_of_elements; layer++)
    {
        const std::string layerType = Util::getJsonPair(
            "type", 
            layers->elements[layer]->json_pairs, layers->elements[layer]->num_of_pairs)->str_val->val;
        if(layerType == "tilelayer")
        {
            json_list *layerData = Util::getJsonList(
                "data", 
                layers->elements[layer]->json_lists, layers->elements[layer]->num_of_lists);
            int currentElement = 0;
            for(int row = 0; row < mapTileHeight; row++)
            {
                std::vector<unsigned int> currentRow;
                for(int column = 0; column < mapTileWidth; column++)
                {
                    currentRow.push_back(layerData->elements[currentElement]->int_val->val);
                    currentElement++;
                }
                grid.push_back(currentRow);
            }
        }
        else if(layerType == "objectgroup")
        {
            json_list *objectData = Util::getJsonList(
                "objects", 
                layers->elements[layer]->json_lists, layers->elements[layer]->num_of_lists);
            
            for(int currentObject = 0; currentObject < objectData->num_of_elements; currentObject++)
            {
                json_list_element *objectJson = objectData->elements[currentObject];
                const int mapX = Util::getJsonPair("x", objectJson->json_pairs, objectJson->num_of_pairs)->int_val->val;
                const int mapY = Util::getJsonPair("y", objectJson->json_pairs, objectJson->num_of_pairs)->int_val->val;
                switch(std::stoi(
                    Util::getJsonPair("type", objectJson->json_pairs, objectJson->num_of_pairs)->str_val->val))
                {
                    case 1:
                        objects.push_back(new GateSprite(tileset, GateType::WOOD, mapX, mapY));
                        break;
                    case 2:
                        objects.push_back(new GateSprite(tileset, GateType::STEEL, mapX, mapY));
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Map::refreshBackground(const Window &window) const
{
    window.setTargetTexture(bgTexture);
    window.clear();

    for(int y = 0; y < grid.size(); y++)
    {
        for(int x = 0; x < grid[y].size(); x++)
        {
            const unsigned int tileId = grid[y][x];
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
            window.draw(
                tileset->getTilesetTexture(), 
                { tile->x, tile->y, tileset->getTileWidth(), tileset->getTileHeight() }, 
                dstRect);
        }
    }

    window.resetTargetTexture();
}
