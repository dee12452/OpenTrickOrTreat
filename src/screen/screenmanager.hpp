#ifndef _OPEN_TOT_SCREEN_MANAGER_HPP_
#define _OPEN_TOT_SCREEN_MANAGER_HPP_

#include "launchscreen.hpp"
#include "playscreen.hpp"

class ScreenManager
{
public:
    ScreenManager(const State initialState);
    ScreenManager(const ScreenManager &otherMgr);
    ScreenManager& operator=(const ScreenManager &otherMgr);
    ~ScreenManager();

    void updateScreen(GameState &gameState, const Window &window);
    void drawScreen(const GameState &gameState, const Window &window);

private:
    void changeScreen();

    Screen *currentScreen;
    State currentState;
    bool screenChangeFlag;
};

#endif
