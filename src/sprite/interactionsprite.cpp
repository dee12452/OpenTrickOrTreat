#include "interactionsprite.hpp"

InteractionSprite::InteractionSprite(const SDL_Rect dstRect, int property)
    : MapSprite(nullptr, Const::EMPTY_RECT, dstRect)
    , property(property)
{
    setUnsafeLocationX(dstRect.x);
    setUnsafeLocationY(dstRect.y);
}

InteractionSprite::~InteractionSprite()
{}

void InteractionSprite::draw(const Window &, Map *, const SDL_Rect &, unsigned int)
{}

int InteractionSprite::getProperty() const
{
    return property;
}

void InteractionSprite::onCollide(MapSprite *other)
{
    if(other->isPlayer())
    {
        onInteract(static_cast<PlayerSprite *> (other));
    }
}