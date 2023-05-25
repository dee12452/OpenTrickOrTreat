#include "Util.h"

json_object* Json::findJsonObject(const std::string &name, json_object** jsonObjectArray, int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        if(name == jsonObjectArray[i]->key->val) {
            return jsonObjectArray[i];
        }
    }
    Logger::warn(std::string("Warning: Failed to find Json object ") + name);
    return nullptr;
}

json_list* Json::findJsonList(const std::string &name, json_list **jsonListArray, int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        if(name == jsonListArray[i]->key->val) {
            return jsonListArray[i];
        }
    }
    Logger::warn(std::string("Warning: Failed to find Json list ") + name);
    return nullptr;
}

json_pair* Json::findJsonPair(const std::string &name, json_pair **jsonPairArray, int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        if(name == jsonPairArray[i]->key->val) {
            return jsonPairArray[i];
        }
    }
    Logger::warn(std::string("Warning: Failed to find Json pair ") + name);
    return nullptr;
}