#include "skeletonsprite.hpp"
#include "texturemanager.hpp"

SkeletonSprite::SkeletonSprite()
    : MapSprite(TextureManager::getInstance()->getTexture(
        Const::IMAGE_CHARACTERS_SKELETON), 
        {0, 0, 48, 48}, 
        {0, 0, 48, 48})
{}