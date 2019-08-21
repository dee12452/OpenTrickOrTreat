#include "screenmanager.hpp"


ScreenManager::ScreenManager(State initialState)
    : currentScreen(nullptr), currentState(initialState), screenChangeFlag(false)
{
    changeScreen();
}

ScreenManager::ScreenManager(const ScreenManager & otherMgr)
    : ScreenManager(otherMgr.currentState)
{}

ScreenManager& ScreenManager::operator=(const ScreenManager & otherMgr)
{
    if(currentScreen)
    {
        delete currentScreen;
    }
    currentState = otherMgr.currentState;
    changeScreen();
    return *this;
}

ScreenManager::~ScreenManager()
{
    if(currentScreen)
    {
        delete currentScreen;
    }
    currentScreen = nullptr;
}

void ScreenManager::changeScreen()
{
    screenChangeFlag = true;
    if(currentScreen)
    {
        delete currentScreen;
    }
    switch(currentState)
    {
        case State::LAUNCH:
            currentScreen = new LaunchScreen();
            break;
        case State::PLAY:
            currentScreen = new PlayScreen();
            break;
        default:
            currentScreen = nullptr;
            break;
    }
}

void ScreenManager::updateScreen(GameState &gameState, const Window &window)
{
    if(gameState.getState() != currentState)
    {
        currentState = gameState.getState();
        changeScreen();
    }
    if(currentScreen)
    {
        if(screenChangeFlag)
        {
            currentScreen->start(gameState, window);
            screenChangeFlag = false;
        }
        currentScreen->update(gameState);
    }
    else
    {
        Util::log("No screen loaded, closing game.");
        gameState.setState(State::STOP);
    }
}

void ScreenManager::drawScreen(const GameState & /*gameState*/, const Window &window)
{
    if(currentScreen)
    {
        window.clear();
        currentScreen->draw(window);
        window.render();
    }
}
