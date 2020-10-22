#include "treatdropsprite.hpp"
#include "map/map.hpp"
#include "playersprite.hpp"

const std::vector<SDL_Rect> TreatDropSprite::TREAT_DROP_SPRITE_SRC_RECTS = 
{
    {240, 0, 48, 48},
    {288, 0, 48, 48}
};
const unsigned int TreatDropSprite::NUM_OF_CANDIES = 3;
const unsigned int TreatDropSprite::NUM_OF_COINS = 0;

static SDL_Rect getTreatDropDst(Tileset *tileset, const SDL_Rect &srcRect, const SDL_Point &mapLoc)
{
    return
    {
        mapLoc.x - mapLoc.x % tileset->getTileWidth(),
        mapLoc.y - mapLoc.y % tileset->getTileHeight(),
        srcRect.w,
        srcRect.h
    };
}

static SDL_Point getTreatExplosionLocation(const SDL_Rect &objDst)
{
    return {objDst.x + objDst.w / 2, objDst.y};
}

TreatDropSprite::TreatDropSprite(Tileset *tileset, const SDL_Point &mapLoc, TreatDropType type)
    : ObjectSprite(
        tileset->getTilesetTexture()
        , TREAT_DROP_SPRITE_SRC_RECTS[static_cast<unsigned int> (type)]
        , getTreatDropDst(tileset, TREAT_DROP_SPRITE_SRC_RECTS[static_cast<unsigned int> (type)], mapLoc))
    , type(type)
    , collected(false)
    , treatExplosionSprite(
        getTreatExplosionLocation(getDestinationRect())
        , NUM_OF_COINS
        , NUM_OF_CANDIES)
{}

void TreatDropSprite::draw(const Window &window) const
{
    ObjectSprite::draw(window);
    if(collected)
    {
        treatExplosionSprite.draw(window);
    }
}

void TreatDropSprite::update(unsigned int deltaTime, Map *map)
{
    ObjectSprite::update(deltaTime, map);
    if(!collected && this->isColliding(map->getPlayer()))
    {
        collected = true;
    }
    else if(collected)
    {
        treatExplosionSprite.update(deltaTime, map);
    }
    
}

ObjectType TreatDropSprite::getType() const
{
    return TREAT_DROP;
}

bool TreatDropSprite::isBlocking() const
{
    return true;
}