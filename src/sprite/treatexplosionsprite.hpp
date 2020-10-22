#ifndef _OPEN_TOT_TREAT_EXPLOSION_HPP_
#define _OPEN_TOT_TREAT_EXPLOSION_HPP_

#include "mapsprite.hpp"

struct Treat
{
    SDL_Rect src;
    SDL_Rect srcWhite;
    SDL_Rect dst;
    int displacement;
    unsigned int animationDelta;
};

class TreatExplosionSprite : public MapSprite
{
private:
    static const std::vector<SDL_Rect> TREAT_SRC_RECTS;
    static const std::vector<SDL_Point> TREAT_WHITE_SRC_POINTS;
    static const unsigned int TREAT_SPAWN_DELAY;
    static const unsigned int TREAT_ANIMATION_DURATION;
    static const unsigned int TREAT_ANIMATION_Y_DISPLACEMENT;

public:
    TreatExplosionSprite(const SDL_Point &mapLoc, unsigned int numCoins, unsigned int numCandies);

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;

private:
    SDL_Point location;
    std::vector<Treat> treats;
    unsigned int treatSpawnDelta;
    unsigned int numCoins;
    unsigned int numCandies;

    void addTreat(const SDL_Rect &treatSrcRect, const SDL_Rect &treatSrcWhiteRect);
};

#endif