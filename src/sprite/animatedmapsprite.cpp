#include "animatedmapsprite.hpp"

AnimatedMapSprite::AnimatedMapSprite(SDL_Texture *texture, const std::string &animationKey)
    : MapSprite(texture)
    , animation(AnimationManager::getInstance()->getNewAnimation(animationKey))
{
    const SDL_Rect initialSrc = animation->getNext();
    setSourceRect(initialSrc);
    setDestinationRect(initialSrc);
}

AnimatedMapSprite::~AnimatedMapSprite()
{
    delete animation;
}

void AnimatedMapSprite::onUpdate(Map * /*currentMap*/)
{
    setSourceRect(animation->getNext());
}
