#include "witchsprite.hpp"
#include "texturemanager.hpp"

const short int WitchSprite::WITCH_NUMBER_MOVE_ANIMATIONS = 8;
const SDL_Rect WitchSprite::WITCH_INITIAL_SRC = {0, 0, 60, 60};
const unsigned int WitchSprite::SPELL_ANIMATION_DURATION = 650;
const unsigned short int WitchSprite::NUMBER_SPELL_ANIMATIONS = 6;
const int WitchSprite::WITCH_HITBOX_Y_OFFSET = 12;
const int WitchSprite::WITCH_HITBOX_W = 30;
const int WitchSprite::WITCH_HITBOX_H = 30;

WitchSprite::WitchSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_WITCH),
        WITCH_INITIAL_SRC,
        WITCH_INITIAL_SRC,
        WITCH_NUMBER_MOVE_ANIMATIONS,
        WITCH_INITIAL_SRC.h)
    , usingSpell(false)
    , spellAnimationDelta(0)
{}

void WitchSprite::update(unsigned int deltaTime, Map *map)
{
    PlayerSprite::update(deltaTime, map);
    if(usingSpell)
    {
        spellAnimationDelta += deltaTime;
        const unsigned short int currentSpellAnimation = 
            spellAnimationDelta / (SPELL_ANIMATION_DURATION / NUMBER_SPELL_ANIMATIONS);
        if(currentSpellAnimation >= NUMBER_SPELL_ANIMATIONS)
        {
            usingSpell = false;
            setSourceX(0);
            setSourceY(getSourceY() - WITCH_INITIAL_SRC.h);
            spellAnimationDelta = 0;
            spell.resetAnimation();
        }
        else
        {
            setSourceX(WITCH_INITIAL_SRC.w * currentSpellAnimation);
            spell.setAnimationFrame(currentSpellAnimation);
        }
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

void WitchSprite::stop()
{
    if(usingSpell) return;
    PlayerSprite::stop();
}

void WitchSprite::doAction(Map *map)
{
    if(usingSpell) return;

    usingSpell = true;
    setSourceX(0);
    setSourceY(getSourceY() + WITCH_INITIAL_SRC.h);
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
}

CostumeType WitchSprite::getCostume() const
{
    return WITCH;
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

bool WitchSprite::canMove(Map *map, int x, int y)
{
    if(usingSpell) return false;
    return PlayerSprite::canMove(map, x, y);
}

SDL_Rect WitchSprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - WITCH_HITBOX_W / 2,
        center.y - WITCH_HITBOX_H / 2 + WITCH_HITBOX_Y_OFFSET,
        WITCH_HITBOX_W,
        WITCH_HITBOX_H
    };
}