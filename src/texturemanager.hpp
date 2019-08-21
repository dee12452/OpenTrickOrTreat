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

    void loadTexture(const Window &window, const std::string pathToResourceFolder, const std::string imageFileName);
    SDL_Texture * getTexture(const std::string imageFileName) const;

private:
    static TextureManager *instance;

    std::map<std::string, SDL_Texture *> textureMap;
};

#endif
