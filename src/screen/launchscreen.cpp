#include "launchscreen.hpp"
#include "util/const.hpp"

const unsigned int LaunchScreen::LOAD_TIMER_DELAY = 250; 
const char * const LaunchScreen::LOADING_TEXT = "Loading...";
const SDL_Rect LaunchScreen::LOADING_TEXT_DESTINATION_RECT = {0, 0, 400, 100};

LaunchScreen::LaunchScreen() : loadTimer(LOAD_TIMER_DELAY)
{
    fontsToLoad.push_back(Const::FONT_TYPEWRITER);

    texturesToLoad.push_back(Const::IMAGE_CHARACTERS_SKELETON);
    texturesToLoad.push_back(Const::IMAGE_CHARACTERS_WITCH);
    texturesToLoad.push_back(Const::IMAGE_CHARACTERS_MONSTER);
    texturesToLoad.push_back(Const::IMAGE_CHARACTERS_VAMPIRE);
    texturesToLoad.push_back(Const::IMAGE_CHARACTERS_CREATURE);
    texturesToLoad.push_back(Const::IMAGE_TILESET);
    texturesToLoad.push_back(Const::IMAGE_MISC);
}

LaunchScreen::~LaunchScreen()
{}

void LaunchScreen::onStart(const GameState &gameState, const Window & window)
{
    loadTimer.reset();
    pathToResourceFolder = gameState.getResourceFolderPath();
    loadFonts();
    loadingText = TextSprite(
            window
            , LOADING_TEXT
            , Const::FONT_TYPEWRITER
            , Color::WHITE
            , Const::EMPTY_RECT
            , LaunchScreen::LOADING_TEXT_DESTINATION_RECT);
    loadingText.center();
}

void LaunchScreen::onUpdate(GameState & gameState, unsigned int /*deltaTime*/) 
{
    if(texturesToLoad.empty() && loadTimer.check())
    {
        gameState.setState(State::LEVEL);
        return;
    }
    if(gameState.getResourceFolderPath() != pathToResourceFolder)
    {
        pathToResourceFolder = gameState.getResourceFolderPath();
    }
}

void LaunchScreen::onEvent(GameState & /*gameState*/, const SDL_Event & /*event*/) 
{}

void LaunchScreen::onKeyboardUpdate(GameState & /*gameState*/, const unsigned char * /*keyboardState*/) 
{}

void LaunchScreen::onDraw(const Window & window) 
{
    loadingText.draw(window);
    loadNextTexture(window);
}

void LaunchScreen::loadFonts()
{
    for(auto fontToLoad : fontsToLoad)
    {
        FontManager::getInstance()->loadFont(pathToResourceFolder, fontToLoad);
    }
}

void LaunchScreen::loadNextTexture(const Window &window)
{
    if(!texturesToLoad.empty())
    {
        size_t textureIndex = texturesToLoad.size() - 1;
        TextureManager::getInstance()->loadTexture(window, pathToResourceFolder, texturesToLoad[textureIndex]);
        texturesToLoad.pop_back();
    }
}
