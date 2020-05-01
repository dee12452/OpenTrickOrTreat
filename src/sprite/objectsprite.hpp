#ifndef _OPEN_TOT_OBJECT_SPRITE_HPP_
#define _OPEN_TOT_OBJECT_SPRITE_HPP_

#include "mapsprite.hpp"

enum ObjectType
{
    WOODEN_GATE = 1,
    STEEL_GATE = 2,
    TRASH_CAN = 3,
    BOULDER = 4,
    COSTUME_SELECT_SKELETON = 5,
    COSTUME_SELECT_WITCH = 6,
    COSTUME_SELECT_MONSTER = 7,
    COSTUME_SELECT_CREATURE = 8,
    COSTUME_SELECT_VAMPIRE = 9,
};

class ObjectSprite : public MapSprite
{
public:
    ObjectSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~ObjectSprite() override;

    virtual ObjectType getType() const = 0;
    virtual bool isBlocking() const = 0;
};

#endif