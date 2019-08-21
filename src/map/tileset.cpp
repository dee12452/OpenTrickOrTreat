#include "tileset.hpp"

static Tile * createTile(json_list_element *tileElement, int columns, int spacing, int tileW, int tileH);

// Currently only supports one tileset
Tileset::Tileset(const std::string &pathToResourceFolder)
{
    const std::string tilesetFile = pathToResourceFolder + Const::TILESETS_FOLDER_PATH + Const::TILESET_1;
    json *tilesetJson = gahoodson_create_from_file(tilesetFile.c_str());
    json_list *tilesList = Util::getJsonList("tiles", tilesetJson->json_lists, tilesetJson->num_of_lists);
    const int columns = Util::getJsonPair("columns", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int spacing = Util::getJsonPair("spacing", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int tileW = Util::getJsonPair("tilewidth", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int tileH = Util::getJsonPair("tileheight", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    for(int i = 0; i < tilesList->num_of_elements; i++)
    {
        tiles.push_back(createTile(tilesList->elements[i], columns, spacing, tileW, tileH));
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

Tile * createTile(json_list_element *tileElement, int columns, int spacing, int tileW, int tileH)
{
    const int tileId = Util::getJsonPair("id", tileElement->json_pairs, tileElement->num_of_pairs)->int_val->val;
    int tileX = (tileId % columns);
    tileX = (tileX * tileW) + (tileX * spacing);
    int tileY = (tileId / columns);
    tileY = (tileY * tileH) + (tileY * spacing);

    const std::string type = Util::getJsonPair("type", tileElement->json_pairs, tileElement->num_of_pairs)->str_val->val;
    Tile::Type tileType;
    if(type == "GATE")
    {
        tileType = Tile::Type::GATE;
    }
    else if(type == "OBSTACLE")
    {
        tileType = Tile::Type::OBSTACLE;
    }
    else if(type == "GROUND")
    {
        tileType = Tile::Type::GROUND;
    }
    else if(type == "WATER")
    {
        tileType = Tile::Type::WATER;
    }
    else if(type == "SMASHABLE")
    {
        tileType = Tile::Type::SMASHABLE;
    }
    else
    {
        tileType = Tile::Type::IMPASSABLE;
    }

    // TODO: Support gives candy and coins
    return new Tile({tileX, tileY, tileW, tileH}, tileType, false, false);
}
