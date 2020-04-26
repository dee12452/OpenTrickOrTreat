#include "mapsprite.hpp"
#include <algorithm>

const unsigned int MapSprite::MOVEMENT_DELAY_MS = 30;

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
    if(deltaSpeedTimer >= MOVEMENT_DELAY_MS)
    {
        deltaSpeedTimer = 0;
        setX(getX() + speedX);
        setY(getY() + speedY);
        if(speedX != 0)
        {
            onMoveX();
        }
        if(speedY != 0)
        {
            onMoveY();
        }
    }
}

void MapSprite::stopX()
{
    if(speedX != 0)
    {
        onStopX(speedX);
    }
    speedX = 0;
}

void MapSprite::stopY()
{
    if(speedY != 0)
    {
        onStopY(speedY);
    }
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

void MapSprite::onStopX(int)
{}

void MapSprite::onStopY(int)
{}

void MapSprite::onMoveX()
{}

void MapSprite::onMoveY()
{}
