#ifndef _OPEN_TOT_HOUSE_SPRITE_HPP_
#define _OPEN_TOT_HOUSE_SPRITE_HPP_

#include "objectsprite.hpp"
#include "treatexplosionsprite.hpp"
#include "textsprite.hpp"

class Tileset;

enum HouseType
{
    SINGLE_STORY_STANDARD = 1,
    SINGLE_STORY_TRASHY = 2,
    CONDO_STANDARD = 3,
    CONDO_TRASHY = 4,
    MANSION_STANDARD = 5,
    MANSION_TRASHY = 6
};

class HouseSprite : public ObjectSprite
{
private:
    static const std::vector<SDL_Rect> HOUSE_SRC_RECTS;
    static const std::vector<SDL_Point> HOUSE_SRC_HITBOX_CENTERS;
    static const unsigned int HITBOX_BUFFER_PIXELS;
    static const unsigned int NUM_COINS;
    static const unsigned int NUM_CANDIES;
    static const unsigned int TREAT_EXPLOSION_BUFFER_Y_PIXELS;
    static const std::string TRICK_OR_TREAT_MESSAGE;
    static const unsigned int TRICK_OR_TREAT_MESSAGE_W;
    static const unsigned int TRICK_OR_TREAT_MESSAGE_H;
    static const unsigned int TRICK_OR_TREAT_MESSAGE_DURATION;

public:
    /**
     * @param mapPos Different than other objects, this represents where it will be created from the top-left instead of center
     */
    HouseSprite(const Window &window, Tileset *tileset, HouseType houseType, const SDL_Point &mapPos);

    void draw(const Window &window) const override;
    void update(unsigned int deltaTime, Map *map) override;
    ObjectType getType() const override;
    bool isBlocking() const override;
    SDL_Rect getHitbox() const override;

private:
    bool collected;
    HouseType type;
    int hitboxW;
    int hitboxH;
    TreatExplosionSprite treatExplosionSprite;
    TextSprite trickOrTreatTextSprite;
    unsigned int trickOrTreatMessageDelta;
};

#endif