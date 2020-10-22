#ifndef _OPEN_TOT_TREAT_DROP_SPRITE_HPP_
#define _OPEN_TOT_TREAT_DROP_SPRITE_HPP_

#include "objectsprite.hpp"
#include "treatexplosionsprite.hpp"

class Tileset;

enum TreatDropType
{
    DOG_HOUSE = 0,
    WELL = 1
};

class TreatDropSprite : public ObjectSprite
{
private:
    static const std::vector<SDL_Rect> TREAT_DROP_SPRITE_SRC_RECTS;
    static const unsigned int NUM_OF_CANDIES;
    static const unsigned int NUM_OF_COINS;

public:
    TreatDropSprite(Tileset *tileset, const SDL_Point &mapLoc, TreatDropType type);

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;

    ObjectType getType() const override;
    bool isBlocking() const override;

private:
    TreatDropType type;
    bool collected;
    TreatExplosionSprite treatExplosionSprite;
};

#endif