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
private:
    static const unsigned int MOVEMENT_DELAY_MS;

public:
    MapSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~MapSprite() override;
    
    virtual void update(unsigned int deltaTime, Map *map);
    
    virtual void stopX();
    virtual void stopY();

    int getSpeedX() const;
    void setSpeedX(int speedX);
    
    int getSpeedY() const;
    void setSpeedY(int speedY);

    Direction getMoveDirection() const;
    Direction getFacingDirection() const;

    Tile * getTile(Map *map, unsigned int x, unsigned int y) const;

protected:
    virtual bool canMove(Map *map);
    virtual void onStopX(int previousSpeed);
    virtual void onStopY(int previousSpeed);
    virtual void onMoveX();
    virtual void onMoveY();

    ObjectSprite * findObject(Map *map, int x, int y) const;

private:
    int speedX;
    int speedY;
    unsigned int deltaSpeedTimer;
    Direction direction;
};

#endif
