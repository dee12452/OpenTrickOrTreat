#include "spritefactory.hpp"
#include "texturemanager.hpp"
#include "consumablesprite.hpp"
#include "costumeselectsprite.hpp"

MapSprite * SpriteFactory::generateSprite(const MapObject *mapObject)
{
    SDL_Texture *mapSpriteTexture = TextureManager::getInstance()->getTexture(Const::IMAGE_TOT_3);
    MapSprite *newSprite = nullptr;
    if(mapObject->objectType == "skeleton")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_SKELETON, CostumeType::SKELETON);
    }
    else if(mapObject->objectType == "witch")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_WITCH, CostumeType::WITCH);
    }
    else if(mapObject->objectType == "monster")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_MONSTER, CostumeType::MONSTER);
    }
    else if(mapObject->objectType == "vampire")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_VAMPIRE, CostumeType::VAMPIRE);
    }
    else if(mapObject->objectType == "fish")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_FISH, CostumeType::FISH);
    }
    else if(mapObject->objectType == "candy")
    {
        newSprite = new ConsumableSprite(mapSpriteTexture, Const::ANIMATION_CANDY, ConsumableType::CANDY);
    }
    else if(mapObject->objectType == "coin")
    {
        newSprite = new ConsumableSprite(mapSpriteTexture, Const::ANIMATION_COIN, ConsumableType::COIN);
    }
    else
    {
        Util::criticalError("Failed to create map sprite object %s", mapObject->objectType.c_str());
    }
    return newSprite;
}
