#ifndef _OPEN_TOT_PLAYER_SPRITE_HPP_
#define _OPEN_TOT_PLAYER_SPRITE_HPP_

#include "mapsprite.hpp"
#include "util/timer.hpp"

class PlayerSprite : public MapSprite
{
private:
    static const unsigned int WALK_ANIMATION_CYCLE_LENGTH;
    static const unsigned short int WALK_BUFFER_PIXELS;

public:
    PlayerSprite(
        SDL_Texture *texture,
        const SDL_Rect &sourceRect,
        const SDL_Rect &destinationRect,
        unsigned short int walkAnimations);
    PlayerSprite(
        SDL_Texture *texture,
        const SDL_Rect &sourceRect,
        const SDL_Rect &destinationRect,
        unsigned short int walkAnimations,
        unsigned int walkDirectionAnimationHeight);
    virtual ~PlayerSprite() override;

    virtual void update(unsigned int deltaTime, Map *map) override;
    virtual void draw(const Window &window) const override;
    virtual void stop() override;
    virtual void doAction(Map *map) = 0;

protected:
    virtual void onMoveX() override;
    virtual void onMoveY() override;
    virtual bool canMove(Map *map, unsigned int x, unsigned int y) override;

private:
    SDL_Rect initialSource;
    unsigned short int numWalkAnimations;
    unsigned int walkDeltaTime;
    bool walking;
    unsigned int walkDirectionAnimationHeight;
};

#endif