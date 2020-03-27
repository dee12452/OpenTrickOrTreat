#include "mapsprite.hpp"
#include <algorithm>

MapSprite::MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect)
    : Sprite(texture, sourceRect, destinationRect)
{
    stopX();
    stopY();
}

MapSprite::~MapSprite()
{}

void MapSprite::draw(const Window &window)
{
    const SDL_Rect dstRectCentered = { getX() - getWidth() / 2, getY() - getHeight() / 2, getWidth(), getHeight() };
    window.draw(getSdlTexture(), getSourceRect(), dstRectCentered);
}

void MapSprite::update()
{
    offsetX += speedX;
    offsetY += speedY;
    if(offsetX >= 1.0f)
    {
        setX(getX() + 1);
        offsetX -= 1.0f;
    }
    if(offsetY >= 1.0f)
    {
        setY(getY() + 1);
        offsetY -= 1.0f;
    }
}

void MapSprite::stopX()
{
    speedX = 0;
    offsetX = 0;
}

void MapSprite::stopY()
{
    speedY = 0;
    offsetY = 0;
}

float MapSprite::getSpeedX() const
{
    return speedX;
}

void MapSprite::setSpeedX(float speedX)
{
    this->speedX = std::max(speedX, 1.0f);
}

float MapSprite::getSpeedY() const
{
    return speedY;
}

void MapSprite::setSpeedY(float speedY)
{
    this->speedY = std::max(speedY, 1.0f);
}

void MapSprite::clampX(int mapWidth, int tileWidth)
{
    const int mapWidthPixels = mapWidth * tileWidth;
    setX(std::max(getX() - getWidth() / 2, 0));
    setX(std::min(getX() + getWidth() / 2, mapWidthPixels));
}

void MapSprite::clampY(int mapHeight, int tileHeight)
{
    const int mapHeightPixels = mapHeight * tileHeight;
    setX(std::max(getY() - getHeight() / 2, 0));
    setX(std::min(getY() + getHeight() / 2, mapHeightPixels));
}
