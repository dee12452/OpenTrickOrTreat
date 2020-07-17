#ifndef _OPEN_TOT_OBJECT_SPRITE_HPP_
#define _OPEN_TOT_OBJECT_SPRITE_HPP_

#include "mapsprite.hpp"

enum ObjectType
{
    GATE = 1,
    BREAKABLE = 2,
    COSTUME_SELECT = 3,
    GHOST = 4,
    CANDY = 5,
    COIN = 6
};

class ObjectSprite : public MapSprite
{
public:
    ObjectSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~ObjectSprite() override;

    virtual ObjectType getType() const = 0;
    virtual bool isBlocking() const = 0;
    
    bool isConsumed() const;

protected:
    bool consumed;
};

#endif