#ifndef _OPEN_TOT_CANDY_SPRITE_HPP_
#define _OPEN_TOT_CANDY_SPRITE_HPP_

#include "objectsprite.hpp"

class Tileset;

class CandySprite : public ObjectSprite
{
private:
    static const SDL_Rect CANDY_INITIAL_SRC;
    static const unsigned short int CANDY_HITBOX_W;
    static const unsigned short int CANDY_HITBOX_H;
    static const unsigned int CANDY_ANIMATION_DURATION;
    static const unsigned short int CANDY_NUM_ANIMATIONS;

public:
    CandySprite(Tileset *tileset, const SDL_Point &mapPos);

    void update(unsigned int deltaTime, Map *map);
    ObjectType getType() const;
    bool isBlocking() const;

protected:
    SDL_Rect getHitbox() const override;

private:
    unsigned int animationDeltaTime;
};

#endif