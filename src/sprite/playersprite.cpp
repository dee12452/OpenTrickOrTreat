#include "playersprite.hpp"

PlayerSprite::PlayerSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : MapSprite(texture, sourceRect, destinationRect)
{}

PlayerSprite::~PlayerSprite()
{}