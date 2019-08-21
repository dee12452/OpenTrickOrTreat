#include "screen.hpp"

void Screen::start(const GameState &gameState, const Window &window)
{
    onStart(gameState, window);
}

void Screen::update(GameState &gameState)
{
    onUpdate(gameState, deltaTimer.getElapsedMillis());
    onKeyboardUpdate(gameState, SDL_GetKeyboardState(NULL));
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            gameState.setState(State::STOP);
            return;
        }
        else
        {
            onEvent(gameState, event);
        }
    }
    deltaTimer.reset();
}

void Screen::draw(const Window &window)
{
    onDraw(window);
}
