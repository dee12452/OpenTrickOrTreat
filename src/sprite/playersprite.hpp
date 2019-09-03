#ifndef _OPEN_TOT_CHARACTER_HPP_
#define _OPEN_TOT_CHARACTER_HPP_

#include "mapsprite.hpp"
#include "util/timer.hpp"
#include "animation/animationmanager.hpp"

class PlayerSprite : public MapSprite
{
private:
    static const unsigned int ANIMATION_TIMER_DELAY;
    static const unsigned int POWER_TIMER_DELAY;

public:
    PlayerSprite(SDL_Texture *texture);
    PlayerSprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    ~PlayerSprite() override;

    void stop() override;
    bool isPlayer() const override;
    
    CostumeType getCostumeType() const;
    void setCostumeType(CostumeType costumeType);

    void usePower(Map *map);

protected:
    void onUpdate(Map *map) override;
    void onChangeDirection(MoveDirection oldState, MoveDirection newState) override;
    bool canMove(Map *map) const override;

private:
    void animate();
    const SDL_Rect changeCostume(CostumeType costumeType);
    Animation * getDirectionAnimation() const;
    void openGates(Map *map) const;
    void clearAnimations();

    Timer animationTimer;
    Timer powerTimer;
    Animation *upAnimation;
    Animation *downAnimation;
    Animation *leftAnimation;
    Animation *rightAnimation;
    CostumeType currentCostumeType;
    bool usingPower;
};

#endif
