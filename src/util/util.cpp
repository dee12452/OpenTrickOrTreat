#include "util.hpp"
#include <stdlib.h>
#include <time.h>

bool Util::randomSeeded = false;

void Util::log(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    SDL_LogMessageV(
            SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_INFO,
            message, 
            args);
    va_end(args);
}

void Util::criticalError(const char *message, ...) 
{
    va_list args;
    va_start(args, message);

    SDL_LogMessageV(
            SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_INFO,
            message, 
            args);

    va_end(args);
    
    exit(EXIT_FAILURE);
}

void Util::criticalSdlError(const char *message, ...)
{
    va_list args;
    va_start(args, message);

    SDL_LogMessageV(
            SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_INFO,
            message, 
            args);
    SDL_LogMessage(
            SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_INFO,
            "SDLError: %s", 
            SDL_GetError());

    va_end(args);
    
    exit(EXIT_FAILURE);
}

void Util::sdlFuncCheck(int funcReturn, const char *funcName)
{
    if(funcReturn < 0)
    {
        criticalSdlError("Failure when calling %s", funcName);
    }
}

json_object * Util::getJsonObject(const std::string &name, json_object **jsonObjectArray, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(name == jsonObjectArray[i]->key->val)
        {
            return jsonObjectArray[i];
        }
    }
    log("Warning: Failed to find Json object %s", name.c_str());
    return nullptr;
}

json_list * Util::getJsonList(const std::string &name, json_list **jsonListArray, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(name == jsonListArray[i]->key->val)
        {
            return jsonListArray[i];
        }
    }
    log("Warning: Failed to find Json list %s", name.c_str());
    return nullptr;
}

json_pair * Util::getJsonPair(const std::string &name, json_pair **jsonPairArray, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(name == jsonPairArray[i]->key->val)
        {
            return jsonPairArray[i];
        }
    }
    log("Warning: Failed to find Json pair %s", name.c_str());
    return nullptr;
}

int Util::randomNumber(int min, int max)
{
    if(!randomSeeded)
    {
        srand(time(NULL));
        randomSeeded = true;
    }
    return rand() % max + min;
}