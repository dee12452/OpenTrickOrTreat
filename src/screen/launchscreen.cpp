#include "launchscreen.hpp"

const char * const LaunchScreen::LOADING_TEXT = "Loading...";
const SDL_Rect LaunchScreen::LOADING_TEXT_DESTINATION_RECT = {0, 0, 400, 100};

LaunchScreen::LaunchScreen()
{
    fontsToLoad.push_back(Const::FONT_TYPEWRITER);

    animationsToLoad.push_back(Const::ANIMATION_CS_SKELETON);
    animationsToLoad.push_back(Const::ANIMATION_CS_WITCH);
    animationsToLoad.push_back(Const::ANIMATION_CS_MONSTER);
    animationsToLoad.push_back(Const::ANIMATION_CS_VAMPIRE);
    animationsToLoad.push_back(Const::ANIMATION_CS_FISH);
    animationsToLoad.push_back(Const::ANIMATION_CANDY);
    animationsToLoad.push_back(Const::ANIMATION_COIN);

    animationsToLoad.push_back(Const::ANIMATION_SKELETON_MV_UP);
    animationsToLoad.push_back(Const::ANIMATION_SKELETON_MV_DOWN);
    animationsToLoad.push_back(Const::ANIMATION_SKELETON_MV_LEFT);
    animationsToLoad.push_back(Const::ANIMATION_SKELETON_MV_RIGHT);
    animationsToLoad.push_back(Const::ANIMATION_WITCH_MV_UP);
    animationsToLoad.push_back(Const::ANIMATION_WITCH_MV_DOWN);
    animationsToLoad.push_back(Const::ANIMATION_WITCH_MV_LEFT);
    animationsToLoad.push_back(Const::ANIMATION_WITCH_MV_RIGHT);

    texturesToLoad.push_back(Const::IMAGE_TOT_1);
    texturesToLoad.push_back(Const::IMAGE_TOT_2);
    texturesToLoad.push_back(Const::IMAGE_TOT_3);
}

LaunchScreen::~LaunchScreen()
{}

void LaunchScreen::onStart(const GameState &gameState, const Window & window)
{
    pathToResourceFolder = gameState.getResourceFolderPath();
    loadFonts();
    loadAnimations();
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
    if(texturesToLoad.empty())
    {
        gameState.setState(State::PLAY);
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

void LaunchScreen::loadAnimations()
{
    for(auto animationToLoad : animationsToLoad)
    {
        AnimationManager::getInstance()->loadAnimation(pathToResourceFolder, animationToLoad);
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
