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
    static const SDL_Point SHADOW_SRC_CENTER;

public:
    CandySprite(Tileset *tileset, const SDL_Point &mapPos);

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;
    ObjectType getType() const override;
    bool isBlocking() const override;

protected:
    SDL_Rect getHitbox() const override;

private:
    unsigned int animationDeltaTime;
};

#endif