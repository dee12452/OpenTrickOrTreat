#include "animationmanager.hpp"

AnimationManager * AnimationManager::instance = nullptr;

AnimationManager * AnimationManager::getInstance()
{
    if(!instance)
    {
        instance = new AnimationManager();
    }
    return instance;
}

void AnimationManager::destroyInstance()
{
    delete instance;
    instance = nullptr;
}

void AnimationManager::loadAnimation(const std::string &pathToResourceFolder, const std::string &animationFile)
{
    json *animationJson = gahoodson_create_from_file((pathToResourceFolder + Const::ANIMATIONS_FOLDER_PATH + animationFile).c_str());
    json_object *initialSrcObj = Util::getJsonObject("initial_src", animationJson->objects, animationJson->num_of_objects);
    SDL_Rect initialSrc = {
        Util::getJsonPair("x", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
        , Util::getJsonPair("y", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
        , Util::getJsonPair("w", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
        , Util::getJsonPair("h", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
    };

    animationMap.insert(std::pair<std::string, Animation>(animationFile, Animation(
                    initialSrc
                    , Util::getJsonPair("d_x", animationJson->pairs, animationJson->num_of_pairs)->int_val->val
                    , Util::getJsonPair("d_y", animationJson->pairs, animationJson->num_of_pairs)->int_val->val
                    , Util::getJsonPair("d_w", animationJson->pairs, animationJson->num_of_pairs)->int_val->val
                    , Util::getJsonPair("d_h", animationJson->pairs, animationJson->num_of_pairs)->int_val->val
                    , Util::getJsonPair("iterations", animationJson->pairs, animationJson->num_of_pairs)->int_val->val
                    , Util::getJsonPair("delay_ms", animationJson->pairs, animationJson->num_of_pairs)->int_val->val)
                )
    );

    gahoodson_delete(animationJson);
}

Animation AnimationManager::getAnimation(const std::string &animationKey)
{
    auto animationIterator = animationMap.find(animationKey);
    if(animationIterator == animationMap.end())
    {
        Util::criticalError("Tried getting animation %s, which was not yet loaded", animationKey.c_str());
    }
    return animationIterator->second;
}

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{}

Animation::~Animation()
{}

const SDL_Rect & Animation::getNext()
{
    if(animationTimer.check())
    {
        if(currentIteration >= iterationsBeforeReset)
        {
            currentIteration = 0;
            src = initialSrc;
        }
        else 
        {
            src.x += deltaX;
            src.y += deltaY;
            src.w += deltaW;
            src.h += deltaH;
            currentIteration++;
        }
        animationTimer.reset();
    }
    return src;
}

Animation::Animation(const SDL_Rect & initSrc
        , int dX
        , int dY
        , int dW
        , int dH
        , unsigned int iterations
        , unsigned int animDelayMs)
    : initialSrc(initSrc)
    , src(initSrc)
    , deltaX(dX)
    , deltaY(dY)
    , deltaW(dW)
    , deltaH(dH)
    , currentIteration(0)
    , iterationsBeforeReset(iterations)
    , animationTimer(animDelayMs)
{}
