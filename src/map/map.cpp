#include "map.hpp"
#include "properties.hpp"
#include <math.h>

const char * const Map::TILE_LAYER_IDENTIFIER = "tilelayer";
const char * const Map::OBJECT_LAYER_IDENTIFIER = "objectgroup";

static unsigned int getNextNumber(const std::string &str, unsigned int &currIndex);

Map::Map(const Window &window
        , const std::string &pathToResourceFolder
        , const std::string &mapFile
        , const Tileset *tileset)
{
    const std::string mapFilePath = pathToResourceFolder + Const::MAPS_FOLDER_PATH + mapFile;
    json *mapJson = gahoodson_create_from_file(mapFilePath.c_str());
    tileColumns = Util::getJsonPair("width", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    tileRows = Util::getJsonPair("height", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    tileW = Util::getJsonPair("tilewidth", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    tileH = Util::getJsonPair("tileheight", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    json_list *layersList = Util::getJsonList("layers", mapJson->json_lists, mapJson->num_of_lists);
    for(int layer = 0; layer < layersList->num_of_elements; layer++)
    {
        const json_list_element *layerElement = layersList->elements[layer];
        const std::string layerIdentifier = Util::getJsonPair("type", layerElement->json_pairs, layerElement->num_of_pairs)->str_val->val;
        const std::string layerName = Util::getJsonPair("name", layerElement->json_pairs, layerElement->num_of_pairs)->str_val->val;

        // Create Tile Layer
        if(layerIdentifier == TILE_LAYER_IDENTIFIER)
        {
            json_list *data = Util::getJsonList("data", layerElement->json_lists, layerElement->num_of_lists);
            Tile ***tileGrid = new Tile **[tileRows];
            for(unsigned int i = 0; i < tileRows; i++)
            {
                tileGrid[i] = new Tile*[tileColumns];
            }
            for(unsigned int i = 0, row = 0, column = 0; static_cast<int> (i) < data->num_of_elements; i++)
            {
                const int currentTileId = data->elements[i]->int_val->val - 1;
                if(currentTileId < 0) // Hit a blank tile
                {
                    tileGrid[row][column] = nullptr;
                }
                else
                {
                    const Tile *tilesetTile = tileset->getTiles()[currentTileId];
                    tileGrid[row][column] = new Tile(*tilesetTile);
                }
                column++;
                if(column == tileColumns)
                {
                    column = 0;
                    row++;
                }   
            }

            json_object *layerProperties = Util::getJsonObject("properties", layerElement->json_objects, layerElement->num_of_objects);
            if(layerProperties)
            {
                for(int i = 0; i < layerProperties->num_of_pairs; i++)
                {
                    const std::string property = layerProperties->pairs[i]->str_val->val;
                    unsigned int index = 0;
                    unsigned int row = 0, col = 0;
                    col = getNextNumber(property, index);
                    row = getNextNumber(property, index);
                    const unsigned int propertyType = getNextNumber(property, index);
                    switch(propertyType)
                    {
                        case 0:
                        {
                            const unsigned int stairsLayerNumber = getNextNumber(property, index);
                            if(tileGrid[row][col])
                            {
                                tileGrid[row][col]->setProperty(new StairsProperty(stairsLayerNumber));
                            }
                            break;
                        }
                        default:
                            Util::criticalError("Unrecognized propery in map layer %d", propertyType);
                    }
                }
            }

            tileLayers.push_back(tileGrid);
            if(layerTextures.size() == 0)
            {
                createLayer(window, tileset, const_cast<const Tile ***> (tileGrid), Color::BLACK);
            }
            else
            {
                createLayer(window, tileset, const_cast<const Tile ***> (tileGrid));
            }
        }

        // Create Map Consumables
        else if(layerIdentifier == OBJECT_LAYER_IDENTIFIER && layerName == "consumables")
        {
            json_list *objects = Util::getJsonList("objects", layerElement->json_lists, layerElement->num_of_lists);
            for(int objectIndex = 0; objectIndex < objects->num_of_elements; objectIndex++)
            {
                json_list_element *consumableElement = objects->elements[objectIndex];
                Consumable *consumable = new Consumable;
                consumable->objectType = Util::getJsonPair("type", consumableElement->json_pairs, consumableElement->num_of_pairs)->str_val->val;
                consumable->locationX = Util::getJsonPair("x", consumableElement->json_pairs, consumableElement->num_of_pairs)->int_val->val;
                consumable->locationY = Util::getJsonPair("y", consumableElement->json_pairs, consumableElement->num_of_pairs)->int_val->val;
                consumables.push_back(consumable);
            }
        }

        // Unidefined layer type, invalid map
        else
        {
            Util::criticalError("Unidentified layer %s found, skipping", layerIdentifier.c_str());
        }
    }

    json_object *customProperties = Util::getJsonObject("properties", mapJson->objects, mapJson->num_of_objects);
    startLocationX = Util::getJsonPair("startx", customProperties->pairs, customProperties->num_of_pairs)->int_val->val;
    startLocationY = Util::getJsonPair("starty", customProperties->pairs, customProperties->num_of_pairs)->int_val->val;
    cameraWidth = Util::getJsonPair("camerawidth", customProperties->pairs, customProperties->num_of_pairs)->int_val->val;
    cameraHeight = Util::getJsonPair("cameraheight", customProperties->pairs, customProperties->num_of_pairs)->int_val->val;
    
    gahoodson_delete(mapJson);
}

Map::~Map()
{
    for(auto texture : layerTextures)
    {
        SDL_DestroyTexture(texture);
    }
    for(auto tileGrid : tileLayers)
    {
        for(unsigned int row = 0; row < tileRows; row++)
        {
            for(unsigned int col = 0; col < tileColumns; col++)
            {
                Tile *tileToDelete = tileGrid[row][col];
                if(tileToDelete)
                {
                    delete tileToDelete;
                }
                tileGrid[row][col] = nullptr;
            }
            delete [] tileGrid[row];
        }
        delete [] tileGrid;
    }
    for(auto consumable : consumables)
    {
        delete consumable;
    }
}

Tile * Map::getTile(unsigned int layerNumber, int x, int y) const
{
    return tileLayers[layerNumber][y][x]; // y = row, x = column
}

void Map::removeTile(unsigned int layerNumber, int x, int y)
{
    delete tileLayers[layerNumber][y][x];
    tileLayers[layerNumber][y][x] = nullptr;
    if(std::find(layersNeedingRefresh.begin(), layersNeedingRefresh.end(), layerNumber) == layersNeedingRefresh.end())
    {
        layersNeedingRefresh.push_back(layerNumber);
    }
}

const std::string & Map::getLevelName() const
{
    return levelName;
}

unsigned int Map::getTimeToComplete() const
{
    return timeToComplete;
}

unsigned int Map::getTileRows() const
{
    return tileRows;
}

unsigned int Map::getTileColumns() const
{
    return tileColumns;
}

int Map::getStartLocationX() const
{
    return startLocationX;
}

int Map::getStartLocationY() const
{
    return startLocationY;
}

int Map::getMapPixelWidth() const
{
    return tileW * tileColumns;
}

int Map::getMapPixelHeight() const
{
    return tileH * tileRows;
}

int Map::getTilePixelWidth() const
{
    return tileW;
}

int Map::getTilePixelHeight() const
{
    return tileH;
}

unsigned int Map::getCameraWidth() const
{
    return cameraWidth;
}

unsigned int Map::getCameraHeight() const
{
    return cameraHeight;
}

unsigned int Map::getNumberOfLayers() const
{
    return tileLayers.size();
}

const std::vector<Consumable *> & Map::getConsumables() const
{
    return consumables;
}

void Map::drawLayer(
        const Window &window
        , const Tileset *tileset
        , unsigned int layerNumber
        , const SDL_Rect &camera)
{
    if(std::find(layersNeedingRefresh.begin(), layersNeedingRefresh.end(), layerNumber) != layersNeedingRefresh.end())
    {
        refreshLayer(window, tileset, layerNumber);
    }
    window.draw(layerTextures[layerNumber], camera);
    if(layerNumber == getNumberOfLayers() - 1 && !layersNeedingRefresh.empty())
    {
        layersNeedingRefresh.clear();
    }
}

static SDL_Texture * createLayerTexture(
        const Window &window
        , unsigned int tileRows
        , unsigned int tileColumns
        , int tileW
        , int tileH
        , const Tileset *tileset
        , const Tile ***tileGrid
        , const SDL_Color &baseColor)
{
    SDL_Texture *newLayer = window.createTexture(
            tileColumns * tileW
            , tileRows * tileH
            , baseColor);
    window.setTargetTexture(newLayer);
    for(int x = 0; x < static_cast<int> (tileColumns); x++)
    {
        for(int y = 0; y < static_cast<int> (tileRows); y++)
        {
            const Tile *tile = tileGrid[y][x];
            if(tile)
            {
                window.draw(
                        tileset->getTilesetTexture()
                        , tile->getSourceRect()
                        , {x * tileW, y * tileH, tileW, tileH});
            }
        }
    }
    window.resetTargetTexture();
    return newLayer;
}

void Map::createLayer(const Window &window, const Tileset *tileset, const Tile ***tileGrid)
{
    createLayer(window, tileset, tileGrid, Color::TRANSPARENT);
}

void Map::createLayer(
        const Window &window
        , const Tileset *tileset
        , const Tile ***tileGrid
        , const SDL_Color &baseColor)
{
    layerTextures.push_back(createLayerTexture(
                window
                , getTileRows()
                , getTileColumns()
                , getTilePixelWidth()
                , getTilePixelHeight()
                , tileset
                , tileGrid
                , baseColor));
}

void Map::refreshLayer(const Window &window, const Tileset *tileset, unsigned int layerNum)
{
    const SDL_Color baseColor = layerNum == 0 ? Color::BLACK : Color::TRANSPARENT;
    SDL_Texture *newLayer = createLayerTexture(
                window
                , getTileRows()
                , getTileColumns()
                , getTilePixelWidth()
                , getTilePixelHeight()
                , tileset
                , const_cast<const Tile ***> (tileLayers[layerNum])
                , baseColor);
    SDL_DestroyTexture(layerTextures[layerNum]);
    layerTextures[layerNum] = newLayer;
}

unsigned int getNextNumber(const std::string &str, unsigned int &currIndex)
{
    unsigned int value = 0;
    while(currIndex < str.length() && str[currIndex] != ' ')
    {
        value *= 10;
        value += static_cast<unsigned int> (str[currIndex] - '0');
        currIndex++;
    }
    while(currIndex < str.length() && str[currIndex] == ' ')
    {
        currIndex++;
    }
    return value;
}
