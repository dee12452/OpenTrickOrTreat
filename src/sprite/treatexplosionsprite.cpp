#include "treatexplosionsprite.hpp"
#include "texturemanager.hpp"

const std::vector<SDL_Rect> TreatExplosionSprite::TREAT_SRC_RECTS =
{
    {3, 312, 31, 19},
    {73, 311, 22, 22}
};
const unsigned int TreatExplosionSprite::TREAT_SPAWN_DELAY = 100;
const unsigned int TreatExplosionSprite::TREAT_ANIMATION_DURATION = 200;
const unsigned int TreatExplosionSprite::TREAT_ANIMATION_Y_DISPLACEMENT = 100;

TreatExplosionSprite::TreatExplosionSprite(const SDL_Point &mapLoc, unsigned int numCandies, unsigned int numCoins)
    : MapSprite(
        TextureManager::getInstance()->getTexture(Const::IMAGE_MISC)
        , {}
        , {})
    , location(mapLoc)
    , treatSpawnDelta(0)
    , numCoins(numCoins)
    , numCandies(numCandies)
{}

void TreatExplosionSprite::draw(const Window &window) const
{
    for(unsigned int i = 0; i < treats.size(); i++)
    {
        if(treats[i].animationDelta < TREAT_ANIMATION_DURATION) 
            window.draw(getSdlTexture(), treats[i].src, treats[i].dst);
    }
}

void TreatExplosionSprite::update(unsigned int deltaTime, Map *map)
{
    for(unsigned int i = 0; i < treats.size(); i++)
    {
        if(treats[i].animationDelta < TREAT_ANIMATION_DURATION) 
            treats[i].animationDelta += deltaTime;
        else
            continue;
        
        if(treats[i].animationDelta < TREAT_ANIMATION_DURATION / 2)
        {
            treats[i].dst.y = location.y - treats[i].dst.h / 2 - 
                TREAT_ANIMATION_Y_DISPLACEMENT * treats[i].animationDelta / TREAT_ANIMATION_DURATION;
        }
        else
        {
            treats[i].dst.y = location.y - treats[i].dst.h / 2 - 
                TREAT_ANIMATION_Y_DISPLACEMENT +  TREAT_ANIMATION_Y_DISPLACEMENT * treats[i].animationDelta / TREAT_ANIMATION_DURATION;
        }
        
        if(treats[i].displacement % 2)
        {
            treats[i].dst.x = location.x - 
                treats[i].displacement * treats[i].animationDelta / TREAT_ANIMATION_DURATION;
        }
        else
        {
            treats[i].dst.x = location.x +
                treats[i].displacement * treats[i].animationDelta / TREAT_ANIMATION_DURATION;
        }
        
    }

    if(treats.size() < numCoins + numCandies)
    {
        treatSpawnDelta += deltaTime;
        if(treatSpawnDelta >= TREAT_SPAWN_DELAY)
        {
            if(treats.size() < numCoins)
            {
                addTreat(TREAT_SRC_RECTS[1]);
            }
            else
            {
                addTreat(TREAT_SRC_RECTS[0]);
            }
            treatSpawnDelta = 0;
        }
    }
}

void TreatExplosionSprite::addTreat(const SDL_Rect &treatSrcRect)
{
    int treatRand = Util::randomNumber(15, 20);
    treats.push_back(
        {
            treatSrcRect
            , {location.x - treatSrcRect.w / 2, location.y - treatSrcRect.h / 2, treatSrcRect.w, treatSrcRect.h}
            , treatRand
            , 0
        }
    );   
}