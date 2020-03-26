#include "levelscreen.hpp"

LevelScreen::~LevelScreen()
{}

void LevelScreen::onStart(const GameState &gameState, const Window &window)
{}

void LevelScreen::onUpdate(GameState &gameState, unsigned int deltaTime)
{}

void LevelScreen::onEvent(GameState &gameState, const SDL_Event &event)
{}

void LevelScreen::onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState)
{}

void LevelScreen::onDraw(const Window &window)
{}
