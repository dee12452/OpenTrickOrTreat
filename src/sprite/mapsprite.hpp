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
    virtual void setFacingDirection(Direction direction); 

    SDL_Point getCenter() const;
    virtual SDL_Rect getHitbox() const;

protected:
    virtual bool canMove(Map *map, const SDL_Point &pos) const;
    virtual void onMoveX();
    virtual void onMoveY();

    float getOffsetX() const;
    float getOffsetY() const;

    bool isColliding(MapSprite *otherSprite) const;

private:
    float offsetX;
    float offsetY;
    float speedX;
    float speedY;
    Direction facingDirection;
};

#endif
