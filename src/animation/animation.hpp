#ifndef _OPEN_TOT_ANIMATION_HPP_
#define _OPEN_TOT_ANIMATION_HPP_

#include "util/util.hpp"

class Animation
{
public:
    virtual ~Animation() {}
    virtual Animation * copy() = 0;
    virtual const SDL_Rect & getNext() = 0;
    virtual void reset() = 0;
};

#endif
