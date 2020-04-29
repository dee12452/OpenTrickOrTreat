#include "witchsprite.hpp"
#include "texturemanager.hpp"

const short int WitchSprite::WITCH_NUMBER_MOVE_ANIMATIONS = 8;
const SDL_Rect WitchSprite::WITCH_INITIAL_SRC = {0, 0, 60, 60};
const unsigned int WitchSprite::SPELL_ANIMATION_DELAY = 100;
const unsigned short int WitchSprite::NUMBER_SPELL_ANIMATIONS = 6;

WitchSprite::WitchSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_WITCH),
        WITCH_INITIAL_SRC,
        WITCH_INITIAL_SRC,
        WITCH_NUMBER_MOVE_ANIMATIONS,
        WITCH_INITIAL_SRC.h)
    , usingSpell(false)
    , spellTimer(SPELL_ANIMATION_DELAY)
    , currentSpellAnimation(0)
{}

void WitchSprite::update(unsigned int deltaTime, Map *map)
{
    PlayerSprite::update(deltaTime, map);
    if(usingSpell && spellTimer.check())
    {
        if(currentSpellAnimation >= NUMBER_SPELL_ANIMATIONS)
        {
            usingSpell = false;
            currentSpellAnimation = 0;
            setSourceX(0);
            setSourceY(getSourceY() - WITCH_INITIAL_SRC.h);
            spell.resetAnimation();
        }
        else
        {
            setSourceX(WITCH_INITIAL_SRC.w * currentSpellAnimation);
            currentSpellAnimation++;
            spell.nextAnimationFrame();
        }
        spellTimer.reset();
    }
}

void WitchSprite::draw(const Window &window) const
{
    if(usingSpell)
    {
        spell.draw(window);
    }
    PlayerSprite::draw(window);
}

void WitchSprite::doAction(Map *map)
{
    if(usingSpell) return;

    usingSpell = true;
    setSourceX(0);
    setSourceY(getSourceY() + WITCH_INITIAL_SRC.h);
    currentSpellAnimation++;
    switch (getFacingDirection())
    {
        case UP:
            spell.setX(getX() + getWidth() / 2 - spell.getWidth() / 2);
            spell.setY(getY() - spell.getHeight());
            spell.setAngle(180);
            break;
        case LEFT:
            spell.setX(getX() - spell.getWidth());
            spell.setY(getY() + getHeight() / 3 - spell.getHeight() / 2);
            spell.setAngle(90);
            break;
        case RIGHT:
            spell.setX(getX() + getWidth());
            spell.setY(getY() + getHeight() / 3 - spell.getHeight() / 2);
            spell.setAngle(270);
            break;
        default:
            spell.setX(getX() + getWidth() / 2 - spell.getWidth() / 2);
            spell.setY(getY() + getHeight() / 2);
            spell.setAngle(0);
            break;
    }
    spellTimer.reset();
}

void WitchSprite::onStopX(int previousSpeed)
{
    if(usingSpell) return;
    PlayerSprite::onStopX(previousSpeed);
}

void WitchSprite::onStopY(int previousSpeed)
{
    if(usingSpell) return;
    PlayerSprite::onStopY(previousSpeed);
}

void WitchSprite::onMoveX()
{
    if(usingSpell) return;
    PlayerSprite::onMoveX();
}

void WitchSprite::onMoveY()
{
    if(usingSpell) return;
    PlayerSprite::onMoveY();
}

bool WitchSprite::canMove(Map *map)
{
    if(usingSpell) return false;
    return PlayerSprite::canMove(map);
}