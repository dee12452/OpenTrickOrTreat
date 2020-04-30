#ifndef _OPEN_TOT_MAP_SPRITE_HPP_
#define _OPEN_TOT_MAP_SPRITE_HPP_

#include "sprite.hpp"

class ObjectSprite;
class Map;
struct Tile;

enum Direction 
{ 
    NONE, UP, DOWN, LEFT, RIGHT 
};

class MapSprite : public Sprite
{
public:
    MapSprite(
        SDL_Texture *texture, 
        const SDL_Rect &sourceRect, 
        const SDL_Rect &destinationRect);
    MapSprite(
        SDL_Texture *texture, 
        const SDL_Rect &sourceRect, 
        const SDL_Rect &destinationRect,
        Direction facingDirection);
    virtual ~MapSprite() override;
    
    virtual void update(unsigned int deltaTime, Map *map);
    virtual void stop();

    float getSpeedX() const;
    void setSpeedX(float speedX);
    
    float getSpeedY() const;
    void setSpeedY(float speedY);

    Direction getMoveDirection() const;
    Direction getFacingDirection() const;
    Tile * getTile(Map *map, int x, int y) const;

protected:
    virtual bool canMove(Map *map, unsigned int x, unsigned int y);
    virtual void onMoveX();
    virtual void onMoveY();

    ObjectSprite * findObject(Map *map, int x, int y) const;

    float getOffsetX() const;
    float getOffsetY() const;

private:
    float offsetX;
    float offsetY;
    float speedX;
    float speedY;
    Direction facingDirection;
};

#endif
