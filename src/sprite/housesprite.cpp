#include "housesprite.hpp"
#include "playersprite.hpp"
#include "textsprite.hpp"
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
const unsigned int HouseSprite::TREAT_EXPLOSION_BUFFER_Y_PIXELS = 50;
const std::string HouseSprite::TRICK_OR_TREAT_MESSAGE = "Trick or Treat";
const unsigned int HouseSprite::TRICK_OR_TREAT_MESSAGE_W = 115;
const unsigned int HouseSprite::TRICK_OR_TREAT_MESSAGE_H = 15;
const unsigned int HouseSprite::TRICK_OR_TREAT_MESSAGE_DURATION = 2000;

static SDL_Point getTreatExplosionLocation(const SDL_Rect &houseHitbox, unsigned int yOffset)
{
    return 
    {
        houseHitbox.x + houseHitbox.w / 2
        , houseHitbox.y + houseHitbox.h / 2 - static_cast<int> (yOffset)
    };
}

static SDL_Rect getHouseDstRect(
    Tileset *tileset
    , HouseType houseType
    , const SDL_Point &mapPos
    , const std::vector<SDL_Rect> &houseSrcRects)
{
    return 
    {
        mapPos.x - mapPos.x % tileset->getTileWidth()
        , mapPos.y - mapPos.y % tileset->getTileHeight()
        , houseSrcRects[static_cast<unsigned int> (houseType) - 1].w
        , houseSrcRects[static_cast<unsigned int> (houseType) - 1].h
    };
}

HouseSprite::HouseSprite(const Window &window, Tileset *tileset, HouseType houseType, const SDL_Point &mapPos)
    : ObjectSprite(
        tileset->getTilesetTexture()
        , HOUSE_SRC_RECTS[static_cast<unsigned int> (houseType) - 1]
        , getHouseDstRect(tileset, houseType, mapPos, HOUSE_SRC_RECTS))
    , collected(false)
    , type(houseType)
    , hitboxW(tileset->getTileWidth() + HITBOX_BUFFER_PIXELS)
    , hitboxH(tileset->getTileHeight() + HITBOX_BUFFER_PIXELS)
    , treatExplosionSprite(
        getTreatExplosionLocation(getHitbox()
        , TREAT_EXPLOSION_BUFFER_Y_PIXELS)
        , NUM_COINS, NUM_CANDIES)
    , trickOrTreatTextSprite(window, TRICK_OR_TREAT_MESSAGE, Const::FONT_TYPEWRITER, Color::YELLOW)
    , trickOrTreatMessageDelta(0)
{
    setWidth(getSourceWidth());
    setHeight(getSourceHeight());
    setX(mapPos.x - mapPos.x % tileset->getTileWidth());
    setY(mapPos.y - mapPos.y % tileset->getTileHeight());

    trickOrTreatTextSprite.setWidth(TRICK_OR_TREAT_MESSAGE_W);
    trickOrTreatTextSprite.setHeight(TRICK_OR_TREAT_MESSAGE_H);
    const SDL_Point treatExplosionLoc = getTreatExplosionLocation(getHitbox(), TREAT_EXPLOSION_BUFFER_Y_PIXELS);
    trickOrTreatTextSprite.setX(treatExplosionLoc.x - trickOrTreatTextSprite.getWidth() / 2);
    trickOrTreatTextSprite.setY(treatExplosionLoc.y + trickOrTreatTextSprite.getHeight());
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
        if(trickOrTreatMessageDelta < TRICK_OR_TREAT_MESSAGE_DURATION)
        {
            if(trickOrTreatMessageDelta < TRICK_OR_TREAT_MESSAGE_DURATION / 3)
            {
                const unsigned char textAlpha = static_cast<unsigned char> (
                    static_cast<float> (Color::YELLOW.a) * trickOrTreatMessageDelta / (TRICK_OR_TREAT_MESSAGE_DURATION / 3)
                );
                window.drawAlphaModulated(
                    trickOrTreatTextSprite.getSdlTexture()
                    , trickOrTreatTextSprite.getDestinationRect()
                    , textAlpha);
            }
            else if(trickOrTreatMessageDelta > TRICK_OR_TREAT_MESSAGE_DURATION * 2 / 3)
            {
                const unsigned char textAlpha = static_cast<unsigned char> (
                    static_cast<float> (Color::YELLOW.a) * (1.0f - static_cast<float> (trickOrTreatMessageDelta - TRICK_OR_TREAT_MESSAGE_DURATION * 2 / 3)
                        / (TRICK_OR_TREAT_MESSAGE_DURATION / 3))
                );
                window.drawAlphaModulated(
                    trickOrTreatTextSprite.getSdlTexture()
                    , trickOrTreatTextSprite.getDestinationRect()
                    , textAlpha);
            }
            else
            {
                trickOrTreatTextSprite.draw(window);
            }
        }
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
        if(trickOrTreatMessageDelta <= TRICK_OR_TREAT_MESSAGE_DURATION)
        {
            trickOrTreatMessageDelta += deltaTime;
        }
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
    return 
    {
        getX() + hitboxDeltaX - hitboxW / 2
        , getY() + hitboxDeltaY - hitboxH / 2
        , hitboxW
        , hitboxH
    };
}