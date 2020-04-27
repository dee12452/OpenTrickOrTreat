#ifndef _OPEN_TOT_SCREEN_HPP_
#define _OPEN_TOT_SCREEN_HPP_

#include "gamestate.hpp"
#include "texturemanager.hpp"
#include "fontmanager.hpp"
#include "util/timer.hpp"

class Screen
{
public:
    virtual ~Screen() {}

    void start(const GameState &gameState, const Window &window);
    void update(GameState &gameState);
    void draw(const Window &window) const;

protected:
    virtual void onStart(const GameState &gameState, const Window &window) = 0;
    virtual void onUpdate(GameState &gameState, unsigned int deltaTime) = 0;
    virtual void onEvent(GameState &gameState, const SDL_Event &event) = 0;
    virtual void onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState) = 0;
    virtual void onDraw(const Window &window) const = 0;

private:
    Timer deltaTimer;
};

#endif
