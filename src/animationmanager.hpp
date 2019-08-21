#ifndef _OPEN_TOT_ANIMATION_MANAGER_HPP_
#define _OPEN_TOT_ANIMATION_MANAGER_HPP_

#include "util.hpp"
#include "timer.hpp"

class Animation;

class AnimationManager
{
public:
    static AnimationManager * getInstance();
    static void destroyInstance();

    void loadAnimation(const std::string &pathToResourceFolder, const std::string &animationFile);
    Animation getAnimation(const std::string &animationKey);

private:
    AnimationManager();
    ~AnimationManager();

    static AnimationManager * instance;

    std::map<std::string, Animation> animationMap;
};

class Animation
{
public:
    Animation(const SDL_Rect & initialSrc
            , int deltaX
            , int deltaY
            , int deltaW
            , int deltaH
            , unsigned int iterationsBeforeReset
            , unsigned int animationDelayMs);
    ~Animation();

    const SDL_Rect & getNext();

private:
    SDL_Rect initialSrc, src;
    int deltaX, deltaY, deltaW, deltaH;
    unsigned int currentIteration;
    unsigned int iterationsBeforeReset;
    Timer animationTimer;
};

#endif
