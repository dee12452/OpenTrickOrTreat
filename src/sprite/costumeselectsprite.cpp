#include "costumeselectsprite.hpp"
#include "texturemanager.hpp"
#include "map/tileset.hpp"

const std::vector<SDL_Rect> CostumeSelectSprite::COSTUME_SELECT_SRC_RECTS = 
{
    {1 + 33 * 0, 0, 33, 47},
    {1 + 33 * 1, 0, 33, 47},
    {1 + 33 * 2, 0, 33, 47},
    {1 + 33 * 4, 0, 33, 47},
    {1 + 33 * 3, 0, 33, 47}
};
const unsigned short int CostumeSelectSprite::COSTUME_SELECT_NUM_ANIMATIONS = 6;
const unsigned int CostumeSelectSprite::COSTUME_SELECT_ANIMATION_DURATION = 1200;

CostumeSelectSprite::CostumeSelectSprite(Tileset *tileset, CostumeType cstm, const SDL_Point &mapPos)
    : ObjectSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_MISC), 
        COSTUME_SELECT_SRC_RECTS[cstm], 
        COSTUME_SELECT_SRC_RECTS[cstm])
    , costume(cstm)
    , animationDelta(0)
{
    setX(mapPos.x - (mapPos.x % tileset->getTileWidth()) + (tileset->getTileWidth() - getWidth()) / 2);
    setY(mapPos.y - (mapPos.y % tileset->getTileHeight()) + (tileset->getTileHeight() - getHeight()) / 2);
}

void CostumeSelectSprite::update(unsigned int deltaTime, Map *)
{
    animationDelta += deltaTime;
    if(animationDelta > COSTUME_SELECT_ANIMATION_DURATION) animationDelta = animationDelta % COSTUME_SELECT_ANIMATION_DURATION;
    const unsigned short int animationIndex = animationDelta / (COSTUME_SELECT_ANIMATION_DURATION / COSTUME_SELECT_NUM_ANIMATIONS);
    setSourceY(getSourceHeight() * animationIndex);
}

ObjectType CostumeSelectSprite::getType() const
{
    return COSTUME_SELECT;
}

bool CostumeSelectSprite::isBlocking() const
{
    return false;
}

CostumeType CostumeSelectSprite::getCostumeType() const
{
    return costume;
}

void CostumeSelectSprite::setCostumeType(CostumeType cstm)
{
    costume = cstm;
}