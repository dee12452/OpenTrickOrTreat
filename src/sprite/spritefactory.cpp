#include "spritefactory.hpp"
#include "texturemanager.hpp"
#include "consumablesprite.hpp"
#include "costumeselectsprite.hpp"

MapSprite * SpriteFactory::generateSprite(const MapObject *mapObject)
{
    SDL_Texture *mapSpriteTexture = TextureManager::getInstance()->getTexture(Const::IMAGE_TOT_3);
    if(mapObject->objectType == "skeleton")
    {
        return new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_SKELETON, CostumeType::SKELETON);
    }
    else if(mapObject->objectType == "witch")
    {
        return new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_WITCH, CostumeType::WITCH);
    }
    else if(mapObject->objectType == "monster")
    {
        return new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_MONSTER, CostumeType::MONSTER);
    }
    else if(mapObject->objectType == "vampire")
    {
        return new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_VAMPIRE, CostumeType::VAMPIRE);
    }
    else if(mapObject->objectType == "fish")
    {
        return new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_FISH, CostumeType::FISH);
    }
    else if(mapObject->objectType == "candy")
    {
        return new ConsumableSprite(mapSpriteTexture, Const::ANIMATION_CANDY, ConsumableType::CANDY);
    }
    else if(mapObject->objectType == "coin")
    {
        return new ConsumableSprite(mapSpriteTexture, Const::ANIMATION_COIN, ConsumableType::COIN);
    }
    Util::log("Failed to create map sprite, game is likely to crash.");
    return nullptr;
}
