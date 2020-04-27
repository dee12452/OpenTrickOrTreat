#include "playersprite.hpp"

PlayerSprite::PlayerSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : MapSprite(texture, sourceRect, destinationRect)
{}

PlayerSprite::~PlayerSprite()
{}

void PlayerSprite::draw(const Window &window) const
{
    const SDL_Rect dstRectCentered = { getX(), getY() - getHeight() / 3, getWidth(), getHeight() };
    window.draw(getSdlTexture(), getSourceRect(), dstRectCentered);
}