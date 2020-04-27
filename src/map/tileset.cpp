#include "tileset.hpp"
#include "GahoodSON/parse.h"

Tileset::Tileset(const std::string &pathToResourceFolder) 
{
    tilesetTexture = TextureManager::getInstance()->getTexture(Const::IMAGE_TILESET);
    const std::string tilesetFile = pathToResourceFolder + Const::TILESETS_FOLDER_PATH + Const::TILESET_1;
    json *tilesetJson = gahoodson_create_from_file(tilesetFile.c_str());
    const int tileWidth = Util::getJsonPair("tilewidth", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int tileHeight = Util::getJsonPair("tileheight", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int imageWidth = Util::getJsonPair("imagewidth", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int imageHeight = Util::getJsonPair("imageheight", tilesetJson->pairs, tilesetJson->num_of_pairs)->int_val->val;
    const int rows = imageHeight / tileHeight;
    const int columns = imageWidth / tileWidth;
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            Tile *tile = new Tile();
            tile->location = { column * tileWidth, row * tileHeight, tileWidth, tileHeight };
            tile->type = TileType::IMPASSABLE;
            tiles.push_back(tile);
        }
    }
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    json_list *tileList = Util::getJsonList("tiles", tilesetJson->json_lists, tilesetJson->num_of_lists);
    for(int element = 0; element < tileList->num_of_elements; element++)
    {
        json_list_element *tileElement = tileList->elements[element];
        const int tileId = Util::getJsonPair("id", tileElement->json_pairs, tileElement->num_of_pairs)->int_val->val;
        const std::string tileType = Util::getJsonPair("type", tileElement->json_pairs, tileElement->num_of_pairs)->str_val->val;
        if(tileId < 0 || tileId >= tiles.size())
        {
            Util::criticalError("Failed to load tileset: tile id found outside of tile range");
        }
        tiles[tileId]->type = static_cast<TileType> (std::stoi(tileType));
    }
    gahoodson_delete(tilesetJson);
}

Tileset::~Tileset()
{
    for(auto &tile : tiles)
    {
        delete tile;
    }
    tiles.clear();
}

SDL_Texture * Tileset::getTilesetTexture() const
{
    return tilesetTexture;
}

Tile * Tileset::getTile(unsigned int tileNumber) const
{
    if(tileNumber == 0) 
    {
        return nullptr;
    } 
    else if(tileNumber - 1 < tiles.size()) 
    {
        return tiles[tileNumber - 1];
    }
    else
    {
        Util::criticalError("Tried accessing tile %d but there's only %d tiles in the tileset.", tileNumber, tiles.size());
        return nullptr;
    }
}

int Tileset::getTileWidth() const
{
    return tileWidth;
}

int Tileset::getTileHeight() const
{
    return tileHeight;
}
