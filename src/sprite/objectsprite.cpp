#include "objectsprite.hpp"

ObjectSprite::ObjectSprite(
    SDL_Texture *texture, 
    const SDL_Rect &sourceRect, 
    const SDL_Rect &destinationRect)
    : MapSprite(texture, sourceRect, destinationRect)
{}

ObjectSprite::~ObjectSprite()
{}

bool ObjectSprite::isConsumed() const
{
    return consumed;
}