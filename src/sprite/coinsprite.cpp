#include "coinsprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"
#include "playersprite.hpp"

const SDL_Rect CoinSprite::COIN_INITIAL_SRC = {73, 282, 23, 23};
const unsigned int CoinSprite::COIN_ANIMATION_HEIGHT = 28;
const unsigned int CoinSprite::COIN_ANIMATION_DURATION = 450;
const unsigned short int CoinSprite::COIN_NUM_ANIMATIONS = 4;
const SDL_Point CoinSprite::SHADOW_SRC_CENTER = {84, 409};

CoinSprite::CoinSprite(Tileset *tileset, const SDL_Point &mapPos)
    : ObjectSprite(TextureManager::getInstance()->getTexture(Const::IMAGE_MISC),
    COIN_INITIAL_SRC,
    COIN_INITIAL_SRC)
    , animationDeltaTime(0)
{
    const int tileX = mapPos.x - mapPos.x % tileset->getTileWidth();
    const int tileY = mapPos.y - mapPos.y % tileset->getTileHeight();
    setX(tileX + tileset->getTileWidth() / 2 - getWidth() / 2);
    setY(tileY + tileset->getTileHeight() / 2 - getHeight() / 2);
}

void CoinSprite::draw(const Window &window) const
{
    ObjectSprite::draw(window);
    const SDL_Rect shadowSrcRect = {
        SHADOW_SRC_CENTER.x - COIN_INITIAL_SRC.w / 2
        , SHADOW_SRC_CENTER.y - COIN_INITIAL_SRC.h / 2
        , COIN_INITIAL_SRC.w
        , COIN_INITIAL_SRC.h
    };
    const SDL_Point coinDstCenter = getCenter();
    const SDL_Rect shadowDstRect = {
        coinDstCenter.x - COIN_INITIAL_SRC.w / 2
        , coinDstCenter.y + COIN_INITIAL_SRC.h / 2
        , COIN_INITIAL_SRC.w
        , COIN_INITIAL_SRC.h
    };
    window.draw(getSdlTexture(), shadowSrcRect, shadowDstRect);
}

void CoinSprite::update(unsigned int deltaTime, Map *map)
{
    animationDeltaTime += deltaTime;
    if(animationDeltaTime > COIN_ANIMATION_DURATION)
    {
        animationDeltaTime %= COIN_ANIMATION_DURATION;
    }
    const unsigned short int animationIndex = animationDeltaTime / (COIN_ANIMATION_DURATION / COIN_NUM_ANIMATIONS);
    setSourceY(COIN_INITIAL_SRC.y + (COIN_ANIMATION_HEIGHT * animationIndex));
    if(!consumed && !map->getPlayer()->isFlying() && isColliding(map->getPlayer()))
    {
        consumed = true;
    }
}

ObjectType CoinSprite::getType() const
{
    return COIN;
}

bool CoinSprite::isBlocking() const
{
    return false;
}
