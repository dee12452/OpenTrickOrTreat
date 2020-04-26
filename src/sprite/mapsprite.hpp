#ifndef _OPEN_TOT_MAP_SPRITE_HPP_
#define _OPEN_TOT_MAP_SPRITE_HPP_

#include "sprite.hpp"

class MapSprite : public Sprite
{
private:
    static const unsigned int MOVEMENT_DELAY_MS;

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

protected:
    virtual void onStopX(int previousSpeed);
    virtual void onStopY(int previousSpeed);
    virtual void onMoveX();
    virtual void onMoveY();

private:
    int speedX;
    int speedY;
    unsigned int deltaSpeedTimer;
};

#endif
