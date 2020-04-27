#ifndef _OPEN_TOT_TEXTURE_MANAGER_HPP_
#define _OPEN_TOT_TEXTURE_MANAGER_HPP_

#include "window.hpp"

class TextureManager
{
private:
    TextureManager();
    ~TextureManager();

public:
    static TextureManager * getInstance();
    static void destroyInstance();

    bool hasLoadedAll() const;
    void loadNextTexture(const Window &window, const std::string pathToResourceFolder);
    SDL_Texture * getTexture(const std::string imageFileName) const;

private:
    static TextureManager *instance;

    std::vector<std::string> texturesToLoad;
    std::map<std::string, SDL_Texture *> textureMap;
};

#endif
