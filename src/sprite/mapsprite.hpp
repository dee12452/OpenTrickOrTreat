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

    int getSpeedX() const;
    void setSpeedX(int speedX);
    
    int getSpeedY() const;
    void setSpeedY(int speedY);

    void clampX(int minX, int maxX);
    void clampY(int minY, int maxY);

private:
    int speedX;
    int speedY;
    unsigned int deltaSpeedTimer;
};

#endif
