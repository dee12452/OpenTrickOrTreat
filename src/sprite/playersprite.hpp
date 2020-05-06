#ifndef _OPEN_TOT_PLAYER_SPRITE_HPP_
#define _OPEN_TOT_PLAYER_SPRITE_HPP_

#include "mapsprite.hpp"
#include "util/timer.hpp"

class PlayerSprite : public MapSprite
{
private:
    static const unsigned int WALK_ANIMATION_CYCLE_LENGTH;

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
    virtual void stop() override;
    void setFacingDirection(Direction direction) override;
    virtual void doAction(Map *map) = 0;
    virtual CostumeType getCostume() const = 0;
    
    bool isFlying() const;

protected:
    bool flying;

    virtual void onMoveX() override;
    virtual void onMoveY() override;
    virtual bool canMove(Map *map, const SDL_Point &pos) const override;

    void findCollisions(
        Map *map, 
        const SDL_Point &pos, 
        Tile * &tile1, 
        Tile * &tile2, 
        ObjectSprite * &obj1, 
        ObjectSprite * &obj2) const;

private:
    SDL_Rect initialSource;
    unsigned short int numWalkAnimations;
    unsigned int walkDeltaTime;
    bool walking;
    unsigned int walkDirectionAnimationHeight;
};

#endif