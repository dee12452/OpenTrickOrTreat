#include "treatexplosionsprite.hpp"
#include "texturemanager.hpp"

const std::vector<SDL_Rect> TreatExplosionSprite::TREAT_SRC_RECTS =
{
    {3, 312, 31, 19},
    {73, 311, 22, 22}
};
const std::vector<SDL_Point> TreatExplosionSprite::TREAT_WHITE_SRC_POINTS =
{
    {3, 483},
    {73, 427}
};
const unsigned int TreatExplosionSprite::TREAT_SPAWN_DELAY = 100;
const unsigned int TreatExplosionSprite::TREAT_ANIMATION_DURATION = 200;
const unsigned int TreatExplosionSprite::TREAT_ANIMATION_Y_DISPLACEMENT = 100;

TreatExplosionSprite::TreatExplosionSprite(const SDL_Point &mapLoc, unsigned int numCandies, unsigned int numCoins)
    : MapSprite(TextureManager::getInstance()->getTexture(Const::IMAGE_MISC))
    , location(mapLoc)
    , treatSpawnDelta(0)
    , numCoins(numCoins)
    , numCandies(numCandies)
{}

static unsigned char colorByPercentage(unsigned char val, unsigned int currentDelta, unsigned int duration)
{
    return static_cast<unsigned char> (static_cast<float> (val) * currentDelta / duration);
}

void TreatExplosionSprite::draw(const Window &window) const
{
    for(unsigned int i = 0; i < treats.size(); i++)
    {
        if(treats[i].animationDelta < TREAT_ANIMATION_DURATION)
        {
            window.draw(getSdlTexture(), treats[i].src, treats[i].dst);

            const unsigned char whiteAlphaMod = static_cast<unsigned char> (
                static_cast<float> (Color::WHITE.a) * treats[i].animationDelta / TREAT_ANIMATION_DURATION
            );
            window.drawAlphaModulated(
                getSdlTexture()
                , treats[i].srcWhite
                , treats[i].dst
                , whiteAlphaMod);
        }
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
                addTreat(
                    TREAT_SRC_RECTS[1]
                    ,
                    {
                        TREAT_WHITE_SRC_POINTS[1].x
                        , TREAT_WHITE_SRC_POINTS[1].y
                        , TREAT_SRC_RECTS[1].w
                        , TREAT_SRC_RECTS[1].h
                    }
                );
            }
            else
            {
                addTreat(
                    TREAT_SRC_RECTS[0]
                    ,
                    {
                        TREAT_WHITE_SRC_POINTS[0].x
                        , TREAT_WHITE_SRC_POINTS[0].y
                        , TREAT_SRC_RECTS[0].w
                        , TREAT_SRC_RECTS[0].h
                    }
                );
            }
            treatSpawnDelta = 0;
        }
    }
}

void TreatExplosionSprite::addTreat(const SDL_Rect &treatSrcRect, const SDL_Rect &treatSrcWhiteRect)
{
    int treatRand = Util::randomNumber(15, 20);
    treats.push_back(
        {
            treatSrcRect
            , treatSrcWhiteRect
            , {location.x - treatSrcRect.w / 2, location.y - treatSrcRect.h / 2, treatSrcRect.w, treatSrcRect.h}
            , treatRand
            , 0
        }
    );   
}