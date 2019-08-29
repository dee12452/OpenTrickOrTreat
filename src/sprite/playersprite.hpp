#ifndef _OPEN_TOT_CHARACTER_HPP_
#define _OPEN_TOT_CHARACTER_HPP_

#include "mapsprite.hpp"
#include "util/timer.hpp"
#include "animation/animationmanager.hpp"

class PlayerSprite : public MapSprite
{
private:
    static const unsigned int ANIMATION_TIMER_DELAY;

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
    Animation *upAnimation;
    Animation *downAnimation;
    Animation *leftAnimation;
    Animation *rightAnimation;
    CostumeType currentCostumeType;
};

#endif
