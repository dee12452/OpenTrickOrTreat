#ifndef _OPEN_TOT_GHOST_SPRITE_HPP_
#define _OPEN_TOT_GHOST_SPRITE_HPP_

#include "objectsprite.hpp"

class Tileset;

class GhostSprite : public ObjectSprite
{
private:
    static const SDL_Rect GHOST_INITIAL_SRC;
    static const SDL_Rect GHOST_FROG_INITIAL_SRC;
    static const unsigned int GHOST_FROG_ANIMATION_DURATION;
    static const unsigned int GHOST_FROG_ANIMATION_BLINK_DURATION;

public:
    GhostSprite(Tileset *tileset, const std::vector<SDL_Point> &path, const SDL_Point &mapPos);

    void update(unsigned int deltaTime, Map *map) override;
    ObjectType getType() const override;
    bool isBlocking() const override;

    void kill();

protected:
    virtual void onMoveX();
    virtual void onMoveY();

    bool canMove(Map *map, int x, int y) const override;

private:
    std::vector<SDL_Point> path;
    unsigned int currentPathIndex;
    bool movingForward;
    bool dead;
    unsigned int deadDeltaTime;
};

#endif