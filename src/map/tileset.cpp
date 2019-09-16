#include "tileset.hpp"
#include <math.h>
#include "texturemanager.hpp"

static Tile * createTile(json_object *tileObj, int tileId, int columns, int spacing, int tileW, int tileH);
static int tileIdAsInt(char *tileId, int tileIdLength) 
{
    int id = 0;
    for(int i = tileIdLength; i > 0; i--)
    {
        int digit = tileId[i - 1] - '0';
        int power = pow(10, tileIdLength - i);
        if(power > 0)
        {
            digit *= power;
        }
        id += digit;
    }
    return id;
}

// TODO: Support multiple tilesets
// Currently only supports one tileset
Tileset::Tileset(const std::string &pathToResourceFolder)
{
    imageName = Const::IMAGE_TOT_1;
    const std::string tilesetFile = pathToResourceFolder + Const::TILESETS_FOLDER_PATH + Const::TILESET_1;
    json *tilesetJson = gahoodson_create_from_file(tilesetFile.c_str());
    json_object *tileObjects = Util::getJsonObject("tiles", tilesetJson->objects, tilesetJson->num_of_objects);
    const int columns = Util::getJsonPair("columns", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int spacing = Util::getJsonPair("spacing", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int tileW = Util::getJsonPair("tilewidth", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int tileH = Util::getJsonPair("tileheight", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    for(int i = 0; i < tileObjects->num_of_subobjects; i++)
    {
        for(int j = 0; j < tileObjects->num_of_subobjects; j++)
        {
            const int tileId = tileIdAsInt(tileObjects->sub_objects[j]->key->val, tileObjects->sub_objects[j]->key->size);
            if(tileId == i)
            {
                tiles.push_back(createTile(tileObjects->sub_objects[j], tileId, columns, spacing, tileW, tileH));
            }
        }
    }
    gahoodson_delete(tilesetJson);
}

Tileset::~Tileset()
{
    for(Tile *tile : tiles)
    {
        delete tile;
    }
    tiles.clear();
}

const std::string & Tileset::getImageName() const
{
    return imageName;
}

const std::vector<Tile *> & Tileset::getTiles() const
{
    return tiles;
}

SDL_Texture * Tileset::getTilesetTexture() const
{
    return TextureManager::getInstance()->getTexture(imageName);
}

Tile * createTile(json_object *tileObj, int tileId, int columns, int spacing, int tileW, int tileH)
{
    int tileX = (tileId % columns);
    tileX = (tileX * tileW) + (tileX * spacing);
    int tileY = (tileId / columns);
    tileY = (tileY * tileH) + (tileY * spacing);

    const std::string type = Util::getJsonPair("type", tileObj->pairs, tileObj->num_of_pairs)->str_val->val;
    if(type == "GATE")
    {
        return new Tile(tileId, {tileX, tileY, tileW, tileH}, Tile::Type::GATE);
    }
    else if(type == "OBSTACLE")
    {
        return new Tile(tileId, {tileX, tileY, tileW, tileH}, Tile::Type::OBSTACLE);
    }
    else if(type == "GROUND")
    {
        return new Tile(tileId, {tileX, tileY, tileW, tileH}, Tile::Type::GROUND);
    }
    else if(type == "WATER")
    {
        return new Tile(tileId, {tileX, tileY, tileW, tileH}, Tile::Type::WATER);
    }
    else if(type == "SMASHABLE")
    {
        return new Tile(tileId, {tileX, tileY, tileW, tileH}, Tile::Type::SMASHABLE);
    }
    else
    {
        return new Tile(tileId, {tileX, tileY, tileW, tileH}, Tile::Type::IMPASSABLE);
    }
}
