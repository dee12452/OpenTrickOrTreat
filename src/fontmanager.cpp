#include "fontmanager.hpp"

FontManager * FontManager::instance = nullptr;

FontManager::FontManager()
    : fontsToLoad({Const::FONT_TYPEWRITER})
{}

FontManager::~FontManager()
{
    for(auto &fontEntry : fontMap)
    {
        TTF_CloseFont(fontEntry.second);
    }
    fontMap.clear();
}

FontManager * FontManager::getInstance()
{
    if(!FontManager::instance)
    {
        FontManager::instance = new FontManager();
    }
    return FontManager::instance;
}

void FontManager::destroyInstance()
{
    if(FontManager::instance)
    {
        delete FontManager::instance;
    }
    FontManager::instance = nullptr;
}

bool FontManager::hasLoadedAll() const
{
    return fontsToLoad.empty();
}

void FontManager::loadAllFonts(const std::string pathToResourceFolder)
{
    for(auto fontFileName : fontsToLoad)
    {
        const std::string fontFilePath = pathToResourceFolder + Const::FONTS_FOLDER_PATH + fontFileName;
        TTF_Font *loadedFont = TTF_OpenFont(fontFilePath.c_str(), Const::DEFAULT_FONT_PT_SIZE);
        if(!loadedFont)
        {
            Util::criticalSdlError("Failed to load font %s", fontFileName.c_str());
        }
        fontMap.insert(std::pair<std::string, TTF_Font *> (fontFileName, loadedFont));
    }
    fontsToLoad.clear();
}

TTF_Font * FontManager::getFont(const std::string fontFileName) const
{
    auto textureIterator = fontMap.find(fontFileName);
    if(textureIterator != fontMap.end())
    {
        return textureIterator->second;
    }
    else
    {
        Util::criticalError("Tried getting font %s, which was not yet loaded", fontFileName.c_str());
    }
    return NULL;
}
