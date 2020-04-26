#ifndef _OPEN_TOT_MAP_SPRITE_HPP_
#define _OPEN_TOT_MAP_SPRITE_HPP_

#include "sprite.hpp"

class MapSprite : public Sprite
{
public:
    MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~MapSprite() override;

    void draw(const Window &window) override;
    virtual void update(unsigned int deltaTime);
    
    virtual void stopX();
    virtual void stopY();

    float getSpeedX() const;
    void setSpeedX(float speedX);
    
    float getSpeedY() const;
    void setSpeedY(float speedY);

    void clampX(int mapWidth, int tileWidth);
    void clampY(int mapHeight, int tileHeight);

private:
    float speedX, offsetX;
    float speedY, offsetY;
};

#endif
