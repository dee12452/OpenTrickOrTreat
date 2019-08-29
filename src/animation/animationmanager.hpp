#ifndef _OPEN_TOT_ANIMATION_MANAGER_HPP_
#define _OPEN_TOT_ANIMATION_MANAGER_HPP_

#include "deltaanimation.hpp"
#include "movementanimation.hpp"

class AnimationManager
{
public:
    static AnimationManager * getInstance();
    static void destroyInstance();

    void loadAnimation(const std::string &pathToResourceFolder, const std::string &animationFile);
    Animation * getNewAnimation(const std::string &animationKey);

private:
    AnimationManager();
    ~AnimationManager();

    Animation * createDeltaAnimation(json *deltaAnimationJson);
    Animation * createMovementAnimation(json *mvmtAnimationJson);

    static AnimationManager * instance;

    std::map<std::string, Animation *> animationMap;
};

#endif
