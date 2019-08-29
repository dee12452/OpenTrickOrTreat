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
    const std::string animationType = Util::getJsonPair("type", animationJson->pairs, animationJson->num_of_pairs)->str_val->val;

    if(animationType == "delta")
    {
        animationMap.insert(std::pair<std::string, Animation *> (animationFile, createDeltaAnimation(animationJson)));
    }
    else if(animationType == "movement")
    {
        animationMap.insert(std::pair<std::string, Animation *> (animationFile, createMovementAnimation(animationJson)));
    }
    else
    {
        Util::criticalError("Unrecognized animation type %s", animationType.c_str());
    }

    gahoodson_delete(animationJson);
}

Animation * AnimationManager::getNewAnimation(const std::string &animationKey)
{
    auto animationIterator = animationMap.find(animationKey);
    if(animationIterator == animationMap.end())
    {
        Util::criticalError("Tried getting animation %s, which was not yet loaded", animationKey.c_str());
    }
    return animationIterator->second->copy();
}

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{}

Animation * AnimationManager::createDeltaAnimation(json *deltaAnimationJson)
{
    json_object *initialSrcObj = Util::getJsonObject("initial_src", deltaAnimationJson->objects, deltaAnimationJson->num_of_objects);
    SDL_Rect initialSrc = {
        Util::getJsonPair("x", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
        , Util::getJsonPair("y", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
        , Util::getJsonPair("w", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
        , Util::getJsonPair("h", initialSrcObj->pairs, initialSrcObj->num_of_pairs)->int_val->val
    };

    return new DeltaAnimation(
                initialSrc
                , Util::getJsonPair("d_x", deltaAnimationJson->pairs, deltaAnimationJson->num_of_pairs)->int_val->val
                , Util::getJsonPair("d_y", deltaAnimationJson->pairs, deltaAnimationJson->num_of_pairs)->int_val->val
                , Util::getJsonPair("d_w", deltaAnimationJson->pairs, deltaAnimationJson->num_of_pairs)->int_val->val
                , Util::getJsonPair("d_h", deltaAnimationJson->pairs, deltaAnimationJson->num_of_pairs)->int_val->val
                , Util::getJsonPair("iterations", deltaAnimationJson->pairs, deltaAnimationJson->num_of_pairs)->int_val->val
                , Util::getJsonPair("delay_ms", deltaAnimationJson->pairs, deltaAnimationJson->num_of_pairs)->int_val->val);
}

Animation * AnimationManager::createMovementAnimation(json *mvmtAnimationJson)
{
    json_list *rects = Util::getJsonList("rects", mvmtAnimationJson->json_lists, mvmtAnimationJson->num_of_lists);
    SDL_Rect srcRects[rects->num_of_elements];
    for(int i = 0; i < rects->num_of_elements; i++)
    {
        json_list_element *rect = rects->elements[i];
        srcRects[i] = {
            Util::getJsonPair("x", rect->json_pairs, rect->num_of_pairs)->int_val->val
            , Util::getJsonPair("y", rect->json_pairs, rect->num_of_pairs)->int_val->val
            , Util::getJsonPair("w", rect->json_pairs, rect->num_of_pairs)->int_val->val
            , Util::getJsonPair("h", rect->json_pairs, rect->num_of_pairs)->int_val->val
        };
    }

    return new MovementAnimation(srcRects, rects->num_of_elements);
}
