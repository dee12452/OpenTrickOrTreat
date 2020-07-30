#include "launchscreen.hpp"
#include "util/const.hpp"

const unsigned int LaunchScreen::LOAD_TIMER_DELAY = 0; 
const char * const LaunchScreen::LOADING_TEXT = "Loading...";
const SDL_Rect LaunchScreen::LOADING_TEXT_DESTINATION_RECT = {0, 0, 400, 100};

LaunchScreen::LaunchScreen() : loadTimer(LOAD_TIMER_DELAY), loadingText(nullptr)
{}

LaunchScreen::~LaunchScreen()
{
    if(loadingText)
    {
        delete loadingText;
    }
}

void LaunchScreen::onStart(const GameState &gameState, const Window & window)
{
    loadTimer.reset();
    pathToResourceFolder = gameState.getResourceFolderPath();
    FontManager::getInstance()->loadAllFonts(pathToResourceFolder);
    loadingText = new TextSprite(
            window
            , LOADING_TEXT
            , Const::FONT_TYPEWRITER
            , Color::WHITE
            , LaunchScreen::LOADING_TEXT_DESTINATION_RECT);
    loadingText->center();
}

void LaunchScreen::onUpdate(GameState & gameState, unsigned int /*deltaTime*/) 
{
    if(TextureManager::getInstance()->hasLoadedAll() && loadTimer.check())
    {
        gameState.setState(State::LEVEL);
        return;
    }
}

void LaunchScreen::onEvent(GameState & /*gameState*/, const SDL_Event & /*event*/) 
{}

void LaunchScreen::onKeyboardUpdate(GameState & /*gameState*/, const unsigned char * /*keyboardState*/) 
{}

void LaunchScreen::onDraw(const Window & window) const
{
    loadingText->draw(window);
    TextureManager::getInstance()->loadNextTexture(window, pathToResourceFolder);
}
