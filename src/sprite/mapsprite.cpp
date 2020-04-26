#include "mapsprite.hpp"
#include <algorithm>

MapSprite::MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : Sprite(texture, sourceRect, destinationRect)
    , deltaSpeedTimer(0)
{
    stopX();
    stopY();
}

MapSprite::~MapSprite()
{}

void MapSprite::draw(const Window &window)
{
    const SDL_Rect dstRectCentered = { getX(), getY() - getHeight() / 3, getWidth(), getHeight() };
    window.draw(getSdlTexture(), getSourceRect(), dstRectCentered);
}

void MapSprite::update(unsigned int deltaTime)
{
    deltaSpeedTimer += deltaTime;
    if(deltaSpeedTimer >= 30)
    {
        deltaSpeedTimer = 0;
        setX(getX() + speedX);
        setY(getY() + speedY);
    }
}

void MapSprite::stopX()
{
    speedX = 0;
}

void MapSprite::stopY()
{
    speedY = 0;
}

int MapSprite::getSpeedX() const
{
    return speedX;
}

void MapSprite::setSpeedX(int sX)
{
    speedX = sX;
}

int MapSprite::getSpeedY() const
{
    return speedY;
}

void MapSprite::setSpeedY(int sY)
{
    speedY = sY;
}

void MapSprite::clampX(int minX, int maxX)
{
    setX(std::max(getX() - getWidth() / 2, minX));
    setX(std::min(getX() + getWidth() / 2, maxX));
}

void MapSprite::clampY(int minY, int maxY)
{
    setX(std::max(getY() - getHeight() / 2, minY));
    setX(std::min(getY() + getHeight() / 2, maxY));
}
