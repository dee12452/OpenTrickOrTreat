#ifndef _OPEN_TOT_GAME_HPP_
#define _OPEN_TOT_GAME_HPP_

#include "screen/screenmanager.hpp"

class Game
{
public:
    Game();

    void run(int argc, char **argv);

private:
    void init();
    void deinit();
    void update();

    Window *window;
    Timer fpsTimer;
    GameState gameState;
    ScreenManager screenManager;
};

#endif
