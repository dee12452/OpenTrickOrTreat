#include "spritefactory.hpp"
#include "texturemanager.hpp"
#include "consumablesprite.hpp"
#include "costumeselectsprite.hpp"
#include "stairsinteractionsprite.hpp"

MapSprite * SpriteFactory::generateSprite(const Consumable *consumable)
{
    SDL_Texture *mapSpriteTexture = TextureManager::getInstance()->getTexture(Const::IMAGE_TOT_3);
    MapSprite *newSprite = nullptr;
    if(consumable->objectType == "skeleton")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_SKELETON, CostumeType::SKELETON);
    }
    else if(consumable->objectType == "witch")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_WITCH, CostumeType::WITCH);
    }
    else if(consumable->objectType == "monster")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_MONSTER, CostumeType::MONSTER);
    }
    else if(consumable->objectType == "vampire")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_VAMPIRE, CostumeType::VAMPIRE);
    }
    else if(consumable->objectType == "fish")
    {
        newSprite = new CostumeSelectSprite(mapSpriteTexture, Const::ANIMATION_CS_FISH, CostumeType::FISH);
    }
    else if(consumable->objectType == "candy")
    {
        newSprite = new ConsumableSprite(mapSpriteTexture, Const::ANIMATION_CANDY, ConsumableType::CANDY);
    }
    else if(consumable->objectType == "coin")
    {
        newSprite = new ConsumableSprite(mapSpriteTexture, Const::ANIMATION_COIN, ConsumableType::COIN);
    }
    else
    {
        Util::criticalError("Failed to create map sprite object %s", consumable->objectType.c_str());
    }
    return newSprite;
}
