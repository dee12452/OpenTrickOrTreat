#include "sprite.hpp"

Sprite::Sprite()
    : Sprite(nullptr)
{}

Sprite::Sprite(SDL_Texture *texture)
    : Sprite(texture, {0,0,0,0}, {0,0,0,0})
{}

Sprite::Sprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : sdlTexture(texture), srcRect(sourceRect), dstRect(destinationRect)
{}

Sprite::~Sprite()
{}

int Sprite::getX() const
{
    return dstRect.x;
}

int Sprite::getY() const
{
    return dstRect.y;
}

int Sprite::getWidth() const
{
    return dstRect.w;
}

int Sprite::getHeight() const
{
    return dstRect.h;
}

int Sprite::getSourceX() const
{
    return srcRect.x;
}

int Sprite::getSourceY() const
{
    return srcRect.y;
}

int Sprite::getSourceWidth() const
{
    return srcRect.w;
}

int Sprite::getSourceHeight() const
{
    return srcRect.h;
}

void Sprite::setX(int x)
{
    dstRect.x = x;
}

void Sprite::setY(int y)
{
    dstRect.y = y;
}

void Sprite::setWidth(int w)
{
    dstRect.w = w;
}

void Sprite::setHeight(int h)
{
    dstRect.h = h;
}

void Sprite::setSourceX(int x)
{
    srcRect.x = x;
}

void Sprite::setSourceY(int y)
{
    srcRect.y = y;
}

void Sprite::setSourceWidth(int w)
{
    srcRect.w = w;
}

void Sprite::setSourceHeight(int h)
{
    srcRect.h = h;
}

void Sprite::center()
{
    setX(Const::DEFAULT_WINDOW_WIDTH / 2 - getWidth() / 2);
    setY(Const::DEFAULT_WINDOW_HEIGHT / 2 - getHeight() / 2);
}

void Sprite::draw(const Window &window)
{
    window.draw(sdlTexture, srcRect, dstRect);
}

SDL_Texture * Sprite::getSdlTexture() const
{
    return sdlTexture;
}

void Sprite::setSdlTexture(SDL_Texture *newTexture)
{
    sdlTexture = newTexture;
}

SDL_Rect Sprite::getSourceRect() const
{
    return srcRect;
}

void Sprite::setSourceRect(const SDL_Rect &rect)
{
    srcRect = rect;
}

SDL_Rect Sprite::getDestinationRect() const
{
    return dstRect;
}

void Sprite::setDestinationRect(const SDL_Rect &rect)
{
    dstRect = rect;
}
