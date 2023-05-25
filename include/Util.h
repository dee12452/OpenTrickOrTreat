//
// Created by dee12452 on 5/24/23.
//

#ifndef OPENTRICKORTREAT_UTIL_H
#define OPENTRICKORTREAT_UTIL_H

// All Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <enet/enet.h>
#include <box2d/box2d.h>
#include <GahoodSON/GahoodSON.h>

// Useful standard library includes
#include <cmath>
#include <string>
#include <vector>
#include <map>

namespace Compat {
    int getWindowFlags();
    double getPi();
}

namespace Logger {
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
}

namespace Json {
    json_object* findJsonObject(const std::string &name, json_object** jsonObjectArray, int arraySize);
    json_list* findJsonList(const std::string &name, json_list **jsonListArray, int arraySize);
    json_pair* findJsonPair(const std::string &name, json_pair **jsonPairArray, int arraySize);
}

namespace Math {
    template<typename T> T max(T first, T second);
    template<typename T> T min(T first, T second);
    float toRads(float degrees);
    float toDegrees(float rads);
}

class Timer {
public:
    Timer();
    explicit Timer(Uint64 targetMs);

    void reset();
    bool check();
    void setTargetMs(Uint64 targetMs);
    Uint64 getElapsedMillis();

private:
    Uint64 m_target;
    Uint64 m_start;
    Uint64 m_end;
};

#endif