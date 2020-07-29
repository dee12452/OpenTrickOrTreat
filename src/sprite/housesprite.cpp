#include "housesprite.hpp"
#include "playersprite.hpp"
#include "map/map.hpp"

const std::vector<SDL_Rect> HouseSprite::HOUSE_SRC_RECTS =
{
    {528, 192, 240, 192},
    {672, 720, 240, 192},
    {960, 384, 144, 288},
    {672, 384, 144, 288},
    {0, 768, 336, 336},
    {0, 384, 336, 336}
};

const std::vector<SDL_Point> HouseSprite::HOUSE_SRC_HITBOX_CENTERS =
{
    {698, 336},
    {742, 874},
    {1028, 600},
    {738, 600},
    {168, 1028},
    {168, 644}
};

const unsigned int HouseSprite::HITBOX_BUFFER_PIXELS = 12;
const unsigned int HouseSprite::NUM_COINS = 4;
const unsigned int HouseSprite::NUM_CANDIES = 4;

HouseSprite::HouseSprite(Tileset *tileset, HouseType houseType, const SDL_Point &mapPos)
    : ObjectSprite(
        tileset->getTilesetTexture()
        , HOUSE_SRC_RECTS[static_cast<unsigned int> (houseType) - 1]
        , {
            mapPos.x - mapPos.x % tileset->getTileWidth()
            , mapPos.y - mapPos.y % tileset->getTileHeight()
            , HOUSE_SRC_RECTS[static_cast<unsigned int> (houseType) - 1].w
            , HOUSE_SRC_RECTS[static_cast<unsigned int> (houseType) - 1].y
        })
    , collected(false)
    , type(houseType)
    , hitboxW(tileset->getTileWidth() + HITBOX_BUFFER_PIXELS)
    , hitboxH(tileset->getTileHeight() + HITBOX_BUFFER_PIXELS)
    , treatExplosionSprite({getHitbox().x + getHitbox().w / 2, getHitbox().y + getHitbox().h / 2}, NUM_COINS, NUM_CANDIES)
{
    setWidth(getSourceWidth());
    setHeight(getSourceHeight());
    setX(mapPos.x - mapPos.x % tileset->getTileWidth());
    setY(mapPos.y - mapPos.y % tileset->getTileHeight());
}

void HouseSprite::draw(const Window &window) const
{
    if(!collected)
    {
        ObjectSprite::draw(window);
    }
    else
    {
        treatExplosionSprite.draw(window);
    }
    
}

void HouseSprite::update(unsigned int deltaTime, Map *map)
{
    if(!collected)
    {
        collected = isColliding(map->getPlayer());
    }
    else
    {
        treatExplosionSprite.update(deltaTime, map);
    }
    
}

ObjectType HouseSprite::getType() const
{
    return HOUSE;
}

bool HouseSprite::isBlocking() const
{
    /**
     * This object is designed to be drawn above a deactivated house on the map.
     * This will allow the player to walk onto the balcony of the house if there is one.
     */
    return false;
}

SDL_Rect HouseSprite::getHitbox() const
{
    /**
     * Hitbox is supposed to only exist on the door of the house.
     */
    const SDL_Point srcHitboxPoint = HOUSE_SRC_HITBOX_CENTERS[static_cast<unsigned int> (type) - 1];
    const int hitboxDeltaX = srcHitboxPoint.x - getSourceX();
    const int hitboxDeltaY = srcHitboxPoint.y - getSourceY();
    return {getX() + hitboxDeltaX - hitboxW / 2, getY() + hitboxDeltaY - hitboxH / 2, hitboxW, hitboxH};
}