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

struct Hitbox
{
    int width;
    int height;
};

class MapSprite : public Sprite
{
public:
    MapSprite(
        SDL_Texture *texture
        , const SDL_Rect &sourceRect
        , const SDL_Rect &destinationRect);
    MapSprite(
        SDL_Texture *texture
        , const SDL_Rect &sourceRect
        , const SDL_Rect &destinationRect
        , Direction facingDirection);
    MapSprite(
        SDL_Texture *texture
        , const SDL_Rect &sourceRect
        , const SDL_Rect &destinationRect
        , Direction facingDirection
        , const Hitbox &collisionHitbox
        , const Hitbox &blockingHitbox);
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

    const Hitbox & getBlockingHitbox() const;
    void setBlockingHitbox(const Hitbox &hitbox);

    const Hitbox & getCollisionHitbox() const;
    void setCollisionHitbox(const Hitbox &hitbox);

    SDL_Point getCenter() const;

    bool isColliding(MapSprite *otherSprite) const;
    bool isColliding(const SDL_Point &mapLoc, const Hitbox &otherHitbox) const;

    SDL_Rect getHitboxRect(const Hitbox &hitbox) const;

protected:
    virtual bool canMove(Map *map, const SDL_Point &pos) const;
    virtual void onMoveX();
    virtual void onMoveY();

    float getOffsetX() const;
    float getOffsetY() const;

    bool checkHitboxCollision(const SDL_Point &mapLoc1, const Hitbox &hitbox1, const SDL_Point &mapLoc2, const Hitbox &hitbox2) const;

private:
    float offsetX;
    float offsetY;
    float speedX;
    float speedY;
    Direction facingDirection;
    Hitbox blockingHitbox;
    Hitbox collisionHitbox;
};

#endif
