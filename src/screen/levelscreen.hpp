#ifndef _OPEN_TOT_LEVEL_SCREEN_HPP_
#define _OPEN_TOT_LEVEL_SCREEN_HPP_

#include "screen.hpp"

class Tileset;
class Map;

class LevelScreen : public Screen
{
public:
    LevelScreen();
    ~LevelScreen() override;

protected:
    void onStart(const GameState &gameState, const Window &window) override;
    void onUpdate(GameState &gameState, unsigned int deltaTime) override;
    void onEvent(GameState &gameState, const SDL_Event &event) override;
    void onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState) override;
    void onDraw(const Window &window) const override;

private:
    Tileset *tileset;
    Map *map;
};

#endif
