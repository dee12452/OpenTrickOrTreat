#include "map.hpp"
#include "GahoodSON/parse.h"
#include "sprite/skeletonsprite.hpp"
#include "sprite/witchsprite.hpp"
#include "sprite/gatesprite.hpp"
#include "sprite/costumeselectsprite.hpp"
#include "sprite/ghostsprite.hpp"
#include "sprite/monstersprite.hpp"
#include "sprite/breakablesprite.hpp"
#include "sprite/creaturesprite.hpp"
#include "sprite/vampiresprite.hpp"
#include "sprite/candysprite.hpp"
#include "sprite/coinsprite.hpp"
#include "sprite/starballsprite.hpp"
#include "sprite/housesprite.hpp"
#include "sprite/treatdropsprite.hpp"

Map::Map(const Window &window, const std::string &pathToResourceFolder, const std::string &mapFile, Tileset *ts)
    : tileset(ts), refresh(false)
{
    player = new SkeletonSprite();
    const std::string mapPath = pathToResourceFolder + Const::MAPS_FOLDER_PATH + mapFile;
    json *mapJson = gahoodson_create_from_file(mapPath.c_str());
    const int mapTileWidth = Util::getJsonPair("width", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    const int mapTileHeight = Util::getJsonPair("height", mapJson->pairs, mapJson->num_of_pairs)->int_val->val;
    loadMapValues(mapJson);
    loadGrid(window, mapJson, mapTileWidth, mapTileHeight);
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
    for(auto object : objects) 
    {
        if(!object->isConsumed()) object->update(deltaTime, this);
    }
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
    for(auto object : objects) 
    {
        if(!object->isConsumed()) object->draw(window);
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

Tile * Map::findTile(int x, int y) const
{
    const int tileX = x / tileset->getTileWidth();
    const int tileY = y / tileset->getTileHeight();
    if(tileY < 0 || tileY >= grid.size())
    {
        return nullptr;
    }
    if(tileX < 0 || tileX >= grid[tileY].size())
    {
        return nullptr;
    }
    return tileset->getTile(grid[tileY][tileX]);
}

ObjectSprite * Map::findObject(int x, int y) const
{
    SDL_Rect objHitbox;
    for(auto object : objects)
    {
        objHitbox = object->getHitbox();
        if(objHitbox.x <= x && objHitbox.x + objHitbox.w >= x)
        {
            if(objHitbox.y <= y && objHitbox.y + objHitbox.h >= y)
            {
                return object;
            }
        }
    }
    return nullptr;
}

void Map::changePlayerCostume(CostumeType newCostume)
{
    PlayerSprite *newPlayer;
    switch (newCostume)
    {
        case WITCH:
            newPlayer = new WitchSprite();
            break;
        case MONSTER:
            newPlayer = new MonsterSprite();
            break;
        case CREATURE:
            newPlayer = new CreatureSprite();
            break;
        case VAMPIRE:
            newPlayer = new VampireSprite();
            break;
        default:
            newPlayer = new SkeletonSprite();
            break;
    }
    const SDL_Point originalPlayerCenter = player->getCenter();
    newPlayer->setX(originalPlayerCenter.x - newPlayer->getWidth() / 2);
    newPlayer->setY(originalPlayerCenter.y - newPlayer->getHeight() / 2);
    newPlayer->setFacingDirection(player->getFacingDirection());
    delete player;
    player = newPlayer;
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

static json_pair * getObjectPropertyValue(const json_list_element *objectJson, const std::string propertyName)
{
    const json_list *properties = Util::getJsonList("properties", objectJson->json_lists, objectJson->num_of_lists);
    json_list_element *property = nullptr;
    for(int index = 0; index < properties->num_of_elements; index++)
    {
        json_list_element *currentProperty = properties->elements[index];
        const std::string currentPropertyName = Util::getJsonPair("name", currentProperty->json_pairs, currentProperty->num_of_pairs)->str_val->val; 
        if(propertyName == currentPropertyName)
        {
            property = currentProperty;
            break;
        }
    }
    if(!property) Util::criticalError("Failed to load map: failed to find required property %s", propertyName.c_str());
    return Util::getJsonPair("value", property->json_pairs, property->num_of_pairs);
}

static int getNumberMoves(const std::string &pathStr, unsigned int &index, bool *isNeg);
static std::vector<SDL_Point> parsePath(const std::string pathStr, const SDL_Point &mapPos);

void Map::loadGrid(const Window &window, json *mapJson, int mapTileWidth, int mapTileHeight)
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
                const json_list_element *objectJson = objectData->elements[currentObject];
                const int mapX = Util::getJsonPair("x", objectJson->json_pairs, objectJson->num_of_pairs)->int_val->val;
                const int mapY = Util::getJsonPair("y", objectJson->json_pairs, objectJson->num_of_pairs)->int_val->val;
                const SDL_Point mapPos = {mapX, mapY};
                switch(std::stoi(Util::getJsonPair("type", objectJson->json_pairs, objectJson->num_of_pairs)->str_val->val))
                {
                    case GATE:
                    {
                        const json_pair *materialProperty = getObjectPropertyValue(objectJson, "material");
                        objects.push_back(new GateSprite(tileset, static_cast<GateType> (materialProperty->int_val->val), mapPos));
                        break;
                    }
                    case BREAKABLE:
                    {
                        const json_pair *breakableTypeProperty = getObjectPropertyValue(objectJson, "breakableType");
                        objects.push_back(new BreakableSprite(tileset, static_cast<BreakableType> (breakableTypeProperty->int_val->val), mapPos));
                        break;
                    }
                    case COSTUME_SELECT:
                    {
                        const json_pair *costumeProperty = getObjectPropertyValue(objectJson, "costume");
                        objects.push_back(new CostumeSelectSprite(tileset, static_cast<CostumeType> (costumeProperty->int_val->val), mapPos));
                        break;
                    }
                    case GHOST:
                    {
                        const json_pair *pathProperty = getObjectPropertyValue(objectJson, "path");
                        objects.push_back(new GhostSprite(
                            tileset, 
                            parsePath(pathProperty->str_val->val, {mapPos.x / tileset->getTileWidth(), mapPos.y / tileset->getTileHeight()}), 
                            mapPos));
                        break;
                    }
                    case CANDY:
                    {
                        objects.push_back(new CandySprite(tileset, mapPos));
                        break;
                    }
                    case COIN:
                    {
                        objects.push_back(new CoinSprite(tileset, mapPos));
                        break;
                    }
                    case STAR_BALL:
                    {
                        objects.push_back(new StarBallSprite(tileset, mapPos));
                        break;
                    }
                    case HOUSE:
                    {
                        const json_pair *houseTypeProperty = getObjectPropertyValue(objectJson, "houseType");
                        objects.push_back(new HouseSprite(window, tileset, static_cast<HouseType> (houseTypeProperty->int_val->val), mapPos));
                        break;
                    }
                    case TREAT_DROP:
                    {
                        const json_pair *treatDropTypeProperty = getObjectPropertyValue(objectJson, "treatDropType");
                        objects.push_back(new TreatDropSprite(tileset, mapPos,  static_cast<TreatDropType> (treatDropTypeProperty->int_val->val)));
                        break;
                    }
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

static int getNumberMoves(const std::string &pathStr, unsigned int &index, bool *isNeg)
{
    index++;
    *isNeg = pathStr[index] == '-';
    while(index < pathStr.size() && (pathStr[index] < '0' || pathStr[index] > '9')) index++;
    int moves = 0;
    while(index < pathStr.size() && pathStr[index] != ';')
    {
        moves *= 10;
        moves += pathStr[index] - '0';
        index++;
    }
    return moves;
}

static std::vector<SDL_Point> parsePath(const std::string pathStr, const SDL_Point &tilePos)
{
    std::vector<SDL_Point> path;
    path.push_back(tilePos);
    unsigned int index = 0;
    while(index < pathStr.size())
    {
        if(pathStr[index] == 'x')
        {
            int movesX;
            bool isNeg;
            movesX = getNumberMoves(pathStr, index, &isNeg);
            for(int i = 0; i < movesX; i++)
            {
                SDL_Point nextPos = path.back();
                nextPos.x = isNeg ? nextPos.x - 1 : nextPos.x + 1;
                path.push_back(nextPos);
            }
        }
        else
        {
            int movesY;
            bool isNeg;
            movesY = getNumberMoves(pathStr, index, &isNeg);
            for(int i = 0; i < movesY; i++)
            {
                SDL_Point nextPos = path.back();
                nextPos.y = isNeg ? nextPos.y - 1 : nextPos.y + 1;
                path.push_back(nextPos);
            }
        }
        index++;
    }
    return path;
}