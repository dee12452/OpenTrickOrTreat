#include "texturemanager.hpp"

TextureManager * TextureManager::instance = nullptr;

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{
    for(auto &textureEntry : textureMap)
    {
        SDL_DestroyTexture(textureEntry.second);
    }
    textureMap.clear();
}

TextureManager * TextureManager::getInstance()
{
    if(!TextureManager::instance)
    {
        TextureManager::instance = new TextureManager();
    }
    return TextureManager::instance;
}

void TextureManager::destroyInstance()
{
    if(TextureManager::instance)
    {
        delete TextureManager::instance;
    }
    TextureManager::instance = nullptr;
}

void TextureManager::loadTexture(const Window &window, const std::string pathToResourceFolder, const std::string imageFileName)
{
    const std::string imageFilePath = pathToResourceFolder + Const::TEXTURES_FOLDER_PATH + imageFileName;
    SDL_Texture *loadedTexture = IMG_LoadTexture(window.getSdlRenderer(), imageFilePath.c_str());
    if(!loadedTexture)
    {
        Util::criticalSdlError("Failed to load texture %s", imageFileName.c_str());
    }
    textureMap.insert(std::pair<std::string, SDL_Texture *> (imageFileName, loadedTexture));
}

SDL_Texture * TextureManager::getTexture(const std::string imageFileName) const
{
    auto textureIterator = textureMap.find(imageFileName);
    if(textureIterator != textureMap.end())
    {
        return textureIterator->second;
    }
    else
    {
        Util::criticalError("Tried getting texture %s, which was not yet loaded", imageFileName.c_str());
    }
    return nullptr;
}
