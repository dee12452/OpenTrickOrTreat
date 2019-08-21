#include "animatedmapsprite.hpp"

AnimatedMapSprite::AnimatedMapSprite(SDL_Texture *texture, const std::string &animationKey)
    : MapSprite(texture)
    , animation(AnimationManager::getInstance()->getAnimation(animationKey))
{
    const SDL_Rect initialSrc = animation.getNext();
    setSourceRect(initialSrc);
    setDestinationRect(initialSrc);
}

AnimatedMapSprite::~AnimatedMapSprite()
{}

void AnimatedMapSprite::onUpdate(Map * /*currentMap*/)
{
    setSourceRect(animation.getNext());
}
