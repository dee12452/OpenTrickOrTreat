#ifndef _OPEN_TOT_BREAKABLE_SPRITE_HPP_
#define _OPEN_TOT_BREAKABLE_SPRITE_HPP_

#include "objectsprite.hpp"

class Tileset;

enum BreakableType
{
    BOULDER = 0,
    TRASH = 1
};

class BreakableSprite : public ObjectSprite
{
private:
    static const unsigned int BOULDER_SRC_TILE_ID;
    static const unsigned int TRASH_CAN_SRC_TILE_ID;
    static const unsigned int BREAK_ANIMATION_DURATION;
    static const unsigned int BREAK_ANIMATION_UP_DURATION;
    static const unsigned int BREAK_ANIMATION_SRC_W;
    static const unsigned int BREAK_ANIMATION_SRC_H;
    static const unsigned short int BREAK_ANIMATION_NUM_PIECES;

public:
    BreakableSprite(Tileset *tileset, BreakableType type, const SDL_Point &mapPos);

    void update(unsigned int deltaTime, Map *map) override;
    void draw(const Window &window) const override;
    ObjectType getType() const override;
    bool isBlocking() const override;

    void breakObject();

private:
    BreakableType breakableType;
    bool broken;
    unsigned int breakAnimationDelta;
    SDL_Rect breakAnimationSrc;
    std::vector<SDL_Rect> brokenPiecesDst;
};

#endif