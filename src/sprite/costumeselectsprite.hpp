#ifndef _OPEN_TOT_COSTUME_SELECT_SPRITE_HPP_
#define _OPEN_TOT_COSTUME_SELECT_SPRITE_HPP_

#include "objectsprite.hpp"

class Tileset;

class CostumeSelectSprite : public ObjectSprite
{
private:
    static const std::vector<SDL_Rect> COSTUME_SELECT_SRC_RECTS;
    static const unsigned short int COSTUME_SELECT_NUM_ANIMATIONS;
    static const unsigned int COSTUME_SELECT_ANIMATION_DURATION;

public:
    CostumeSelectSprite(Tileset *tileset, CostumeType costume, const SDL_Point &mapPos);

    void update(unsigned int deltaTime, Map *map) override;
    ObjectType getType() const override;
    bool isBlocking() const override;

    CostumeType getCostumeType() const;
    void setCostumeType(CostumeType costume);

private:
    CostumeType costume;
    unsigned int animationDelta;
};

#endif