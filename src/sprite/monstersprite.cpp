#include "monstersprite.hpp"
#include "texturemanager.hpp"

const SDL_Rect MonsterSprite::MONSTER_INITIAL_SRC = {0, 0, 56, 56};
const short int MonsterSprite::MONSTER_NUMBER_MOVE_ANIMATIONS = 8;
const unsigned int MonsterSprite::SMASHING_ANIMATION_DURATION = 600;
const unsigned short int MonsterSprite::NUMBER_SMASHING_ANIMATIONS = 8;
const int MonsterSprite::MONSTER_HITBOX_Y_OFFSET = 12;
const int MonsterSprite::MONSTER_HITBOX_W = 30;
const int MonsterSprite::MONSTER_HITBOX_H = 30;

MonsterSprite::MonsterSprite()
    : PlayerSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_CHARACTERS_MONSTER),
        MONSTER_INITIAL_SRC,
        MONSTER_INITIAL_SRC,
        MONSTER_NUMBER_MOVE_ANIMATIONS,
        MONSTER_INITIAL_SRC.h)
    , smashing(false)
    , smashingAnimationDelta(0)
{}

void MonsterSprite::update(unsigned int deltaTime, Map *map)
{
    PlayerSprite::update(deltaTime, map);
    if(smashing)
    {
        smashingAnimationDelta += deltaTime;
        const unsigned short int currentSmashingAnimation = 
            smashingAnimationDelta / (SMASHING_ANIMATION_DURATION / NUMBER_SMASHING_ANIMATIONS);
        if(currentSmashingAnimation >= NUMBER_SMASHING_ANIMATIONS)
        {
            smashing = false;
            setSourceX(0);
            setSourceY(getSourceY() - MONSTER_INITIAL_SRC.h);
            smashingAnimationDelta = 0;
        }
        else
        {
            setSourceX(MONSTER_INITIAL_SRC.w * currentSmashingAnimation);
        }
    }
}

void MonsterSprite::stop()
{
    if(smashing) return;
    PlayerSprite::stop();
}

void MonsterSprite::doAction(Map *map)
{
    if(smashing) return;
    
    smashing = true;
    setSourceX(0);
    setSourceY(getSourceY() + MONSTER_INITIAL_SRC.h);
}

CostumeType MonsterSprite::getCostume() const
{
    return MONSTER;
}

void MonsterSprite::onMoveX()
{
    if(smashing) return;
    PlayerSprite::onMoveX();
}

void MonsterSprite::onMoveY()
{
    if(smashing) return;
    PlayerSprite::onMoveY();
}

bool MonsterSprite::canMove(Map *map, int x, int y) const
{
    return !smashing && PlayerSprite::canMove(map, x, y);
}

SDL_Rect MonsterSprite::getHitbox() const
{
    const SDL_Point center = getCenter();
    return 
    {
        center.x - MONSTER_HITBOX_W / 2,
        center.y - MONSTER_HITBOX_H / 2 + MONSTER_HITBOX_Y_OFFSET,
        MONSTER_HITBOX_W,
        MONSTER_HITBOX_H
    };
}