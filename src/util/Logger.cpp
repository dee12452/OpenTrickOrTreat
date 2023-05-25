#include "Util.h"

void Logger::debug(const std::string& message) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
}

void Logger::info(const std::string& message) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
}

void Logger::warn(const std::string& message) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
}

void Logger::error(const std::string& message) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
}