#include "spellsprite.hpp"
#include "texturemanager.hpp"

const std::vector<SDL_Rect> SpellSprite::SPELL_ANIMATION_SOURCES = 
{
    {542 + 66 * 0, 0, 66, 68},
    {542 + 66 * 1, 0, 66, 68},
    {542 + 66 * 2, 0, 66, 68},
    {542 + 66 * 3, 0, 66, 68},
    {542 + 66 * 0, 68, 66, 68},
    {542 + 66 * 1, 68, 66, 68}
};

SpellSprite::SpellSprite()
    : MapSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_WITCH),
        SPELL_ANIMATION_SOURCES[0],
        SPELL_ANIMATION_SOURCES[0])
    , currentAnimation(0)
    , angle(0)
{}

void SpellSprite::update(unsigned int deltaTime, Map *map)
{
    MapSprite::update(deltaTime, map);
}

void SpellSprite::draw(const Window &window) const
{
    window.drawRotated(getSdlTexture(), SPELL_ANIMATION_SOURCES[currentAnimation], getDestinationRect(), angle);
}

void SpellSprite::resetAnimation()
{
    currentAnimation = 0;
}

void SpellSprite::setAnimationFrame(unsigned short int currentSpellAnimation)
{
    currentAnimation = currentSpellAnimation;
}

double SpellSprite::getAngle() const
{
    return angle;
}

void SpellSprite::setAngle(double angl)
{
    angle = angl;
}