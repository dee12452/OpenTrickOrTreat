#ifndef _OPEN_TOT_FONT_MANAGER_HPP_
#define _OPEN_TOT_FONT_MANAGER_HPP_

#include "window.hpp"

class FontManager
{
private:
    FontManager();
    ~FontManager();

public:
    static FontManager * getInstance();
    static void destroyInstance();

    void loadFont(const std::string pathToResourceFolder, const std::string fontFileName);
    TTF_Font * getFont(const std::string fontFileName) const;

private:
    static FontManager *instance;

    std::map<std::string, TTF_Font *> fontMap;
};

#endif
