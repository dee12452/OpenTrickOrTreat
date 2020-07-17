#include "starballsprite.hpp"
#include "texturemanager.hpp"
#include "map/map.hpp"
#include "playersprite.hpp"

const SDL_Rect StarBallSprite::STAR_BALL_INITIAL_SRC = {37, 284, 29, 28};
const unsigned int StarBallSprite::STAR_BALL_ANIMATION_DURATION = 750;
const unsigned short int StarBallSprite::STAR_BALL_NUM_ANIMATIONS = 6;
const SDL_Point StarBallSprite::SHADOW_SRC_CENTER = {84, 409};

StarBallSprite::StarBallSprite(Tileset *tileset, const SDL_Point &mapPos)
    : ObjectSprite(TextureManager::getInstance()->getTexture(Const::IMAGE_MISC),
    STAR_BALL_INITIAL_SRC,
    STAR_BALL_INITIAL_SRC)
    , animationDeltaTime(0)
{
    const int tileX = mapPos.x - mapPos.x % tileset->getTileWidth();
    const int tileY = mapPos.y - mapPos.y % tileset->getTileHeight();
    setX(tileX + tileset->getTileWidth() / 2 - getWidth() / 2);
    setY(tileY + tileset->getTileHeight() / 2 - getHeight() / 2);
}

void StarBallSprite::draw(const Window &window) const
{
    ObjectSprite::draw(window);
    const SDL_Rect shadowSrcRect = {
        SHADOW_SRC_CENTER.x - STAR_BALL_INITIAL_SRC.w / 2
        , SHADOW_SRC_CENTER.y - STAR_BALL_INITIAL_SRC.h / 2
        , STAR_BALL_INITIAL_SRC.w
        , STAR_BALL_INITIAL_SRC.h
    };
    const SDL_Point candyDstCenter = getCenter();
    const SDL_Rect shadowDstRect = {
        candyDstCenter.x - STAR_BALL_INITIAL_SRC.w / 2
        , candyDstCenter.y + STAR_BALL_INITIAL_SRC.h / 4
        , STAR_BALL_INITIAL_SRC.w
        , STAR_BALL_INITIAL_SRC.h
    };
    window.draw(getSdlTexture(), shadowSrcRect, shadowDstRect);
}

void StarBallSprite::update(unsigned int deltaTime, Map *map)
{
    animationDeltaTime += deltaTime;
    if(animationDeltaTime > STAR_BALL_ANIMATION_DURATION)
    {
        animationDeltaTime %= STAR_BALL_ANIMATION_DURATION;
    }
    const unsigned short int animationIndex = animationDeltaTime / (STAR_BALL_ANIMATION_DURATION / STAR_BALL_NUM_ANIMATIONS);
    setSourceY(STAR_BALL_INITIAL_SRC.y + STAR_BALL_INITIAL_SRC.h * animationIndex);
    if(!consumed && !map->getPlayer()->isFlying() && isColliding(map->getPlayer()))
    {
        consumed = true;
    }
}

ObjectType StarBallSprite::getType() const
{
    return CANDY;
}

bool StarBallSprite::isBlocking() const
{
    return false;
}
