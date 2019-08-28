#ifndef _OPEN_TOT_CHARACTER_HPP_
#define _OPEN_TOT_CHARACTER_HPP_

#include "mapsprite.hpp"
#include "timer.hpp"

class PlayerSprite : public MapSprite
{
private:
    static const SDL_Rect STARTING_SRC;
    static const unsigned int ANIMATION_TIMER_DELAY;

    //TODO: Get rid of this by fixing the sprite sheet!
    static const SDL_Rect * const MOTION_DOWN_ANIMATION_SRC_RECTS;
    static const unsigned int MOTION_DOWN_ANIMATION_SRC_RECTS_SIZE;
    static const SDL_Rect * const MOTION_UP_ANIMATION_SRC_RECTS;
    static const unsigned int MOTION_UP_ANIMATION_SRC_RECTS_SIZE;

public:
    PlayerSprite(SDL_Texture *texture);
    PlayerSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    ~PlayerSprite() override;

    bool isPlayer() const override;
    
    CostumeType getCostumeType() const;
    void setCostumeType(CostumeType costumeType);

    void doAction(Map *map);

protected:
    void onUpdate(Map *map) override;
    void onChangeDirectionX(MoveDirectionX oldState, MoveDirectionX newState) override;
    void onChangeDirectionY(MoveDirectionY oldState, MoveDirectionY newState) override;

private:
    void animate();
    void onCollide(const MapSprite *otherSprite);
    void openGates(Map *map) const;

    Timer animationTimer;
    CostumeType currentCostumeType;
    unsigned short int currentDownAnimIndex;
    unsigned short int currentUpAnimIndex;
};

#endif
