#include "map.hpp"

const char * const Map::TILE_LAYER_IDENTIFIER = "tilelayer";
const char * const Map::OBJECT_LAYER_IDENTIFIER = "objectgroup";

Map::Map(const std::string &pathToResourceFolder, const std::string &mapFile, Tileset *tileset)
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
            tileLayers.push_back(tileGrid);
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

        // TODO: Create Map Interactions
        else if(layerIdentifier == OBJECT_LAYER_IDENTIFIER && layerName == "interactions")
        {
            json_list *objects = Util::getJsonList("objects", layerElement->json_lists, layerElement->num_of_lists);
            for(int objectIndex = 0; objectIndex < objects->num_of_elements; objectIndex++)
            {
                json_list_element *interactionElement = objects->elements[objectIndex];
                Interaction *interaction = new Interaction;
                interaction->type = Util::getJsonPair("type", interactionElement->json_pairs, interactionElement->num_of_pairs)->str_val->val;
                interaction->x = Util::getJsonPair("x", interactionElement->json_pairs, interactionElement->num_of_pairs)->int_val->val;
                interaction->y = Util::getJsonPair("y", interactionElement->json_pairs, interactionElement->num_of_pairs)->int_val->val;
                interaction->w = Util::getJsonPair("width", interactionElement->json_pairs, interactionElement->num_of_pairs)->int_val->val;
                interaction->h = Util::getJsonPair("height", interactionElement->json_pairs, interactionElement->num_of_pairs)->int_val->val;
                json_object *properties = Util::getJsonObject("properties", interactionElement->json_objects, interactionElement->num_of_objects);
                if(properties && properties->num_of_pairs > 0 && properties->pairs[0]->int_val)
                {
                    interaction->property = properties->pairs[0]->int_val->val;
                }
                else
                {
                    interaction->property = 0;
                }
                interactions.push_back(interaction);
            }

        }

        // Unidefined layer type, ignore these
        else
        {
            Util::log("Unidentified layer %s found, skipping", layerIdentifier.c_str());
            continue;
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
    for(auto interaction : interactions)
    {
        delete interaction;
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

const std::vector<Interaction *> & Map::getInteractions() const
{
    return interactions;
}

void Map::drawLayer(const Window &window
        , unsigned int layerNumber
        , const SDL_Rect &camera
        , SDL_Texture *tilesetTexture)
{
    const int tileW = getTilePixelWidth(), tileH = getTilePixelHeight();
    for(int tileX = camera.x, dstX = 0; tileX <= camera.x + camera.w; tileX++, dstX++)
    {
        if(tileX < 0 || tileX >= static_cast<int> (getTileColumns()))
        {
            continue;
        }

        for(int tileY = camera.y, dstY = 0; tileY <= camera.y + camera.h; tileY++, dstY++)
        {
            if(tileY < 0 || tileY >= static_cast<int> (getTileRows()))
            {
                continue;
            }
            
            const Tile *tile = getTile(layerNumber, tileX, tileY);
            if(tile) // tile == nullptr when none exists on this layer
            {
                window.draw(tilesetTexture, tile->getSourceRect(), {dstX * tileW, dstY * tileH, tileW, tileH});
            }
        }
    }
}
