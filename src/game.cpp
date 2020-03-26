#include "game.hpp"

Game::Game() 
    : window(nullptr), fpsTimer(Const::FPS_CAP_MILLIS), gameState(State::LAUNCH), screenManager(gameState.getState())
{}

void Game::run(int /*argc*/, char ** /*argv*/) 
{
    init();
    while(gameState.getState() != State::STOP)
    {
        update();
    }
    deinit();
}

void Game::init()
{
    Util::sdlFuncCheck(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), "SDL_Init");
    Util::sdlFuncCheck(IMG_Init(IMG_INIT_PNG), "IMG_Init");
    Util::sdlFuncCheck(TTF_Init(), "TTF_Init");

    std::string resourcePath;
    if(SDL_GetBasePath())
    {
        resourcePath = SDL_GetBasePath();
    }
    resourcePath += Const::DATA_FOLDER_PATH;
    gameState.setResourceFolderPath(resourcePath);
    Util::log("Resource path set to %s", resourcePath.c_str());
    window = new Window();
    fpsTimer.reset();
}

void Game::deinit()
{
    FontManager::destroyInstance();
    TextureManager::destroyInstance();
    delete window;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::update()
{
    if(fpsTimer.check())
    {
        screenManager.updateScreen(gameState, *window);
        screenManager.drawScreen(gameState, *window);
        fpsTimer.reset();
    }
    else
    {
        unsigned int msRemaining = Const::FPS_CAP_MILLIS - fpsTimer.getElapsedMillis();
        SDL_Delay(msRemaining);
    }
}
