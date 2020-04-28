#ifndef _OPEN_TOT_PLAYER_SPRITE_HPP_
#define _OPEN_TOT_PLAYER_SPRITE_HPP_

#include "mapsprite.hpp"
#include "util/timer.hpp"

class PlayerSprite : public MapSprite
{
private:
    static const unsigned int WALK_ANIMATION_DELAY;

public:
    PlayerSprite(
        SDL_Texture *texture,
        const SDL_Rect &sourceRect,
        const SDL_Rect &destinationRect,
        unsigned short int walkAnimations);
    virtual ~PlayerSprite() override;

    virtual void draw(const Window &window) const override;
    virtual void doAction(Map *map) = 0;

protected:
    virtual void onStopX(int previousSpeed) override;
    virtual void onStopY(int previousSpeed) override;
    virtual void onMoveX() override;
    virtual void onMoveY() override;
    virtual bool canMove(Map *map) override;

private:
    Timer walkAnimationTimer;
    SDL_Rect initialSource;
    unsigned short int numWalkAnimations;
};

#endif