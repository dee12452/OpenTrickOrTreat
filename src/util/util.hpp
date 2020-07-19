#ifndef _OPEN_TOT_UTIL_HPP_
#define _OPEN_TOT_UTIL_HPP_

#include "const.hpp"
#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GahoodSON/GahoodSON.h>

class Util
{
public:
    static void log(const char *message, ...);
    static void criticalError(const char *message, ...);
    static void criticalSdlError(const char *message, ...);
    static void sdlFuncCheck(int funcReturn, const char *funcName);

    static json_object * getJsonObject(const std::string &name, json_object **jsonObjectArray, int arraySize);
    static json_list * getJsonList(const std::string &name, json_list **jsonListArray, int arraySize);
    static json_pair * getJsonPair(const std::string &name, json_pair **jsonPairArray, int arraySize);

    static int randomNumber(int min, int max);
private:
    Util() {}

    static bool randomSeeded;
};

#endif
