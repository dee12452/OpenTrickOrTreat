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

    bool hasLoadedAll() const;
    void loadAllFonts(const std::string pathToResourceFolder);
    TTF_Font * getFont(const std::string fontFileName) const;

private:
    static FontManager *instance;

    std::vector<std::string> fontsToLoad;
    std::map<std::string, TTF_Font *> fontMap;
};

#endif
