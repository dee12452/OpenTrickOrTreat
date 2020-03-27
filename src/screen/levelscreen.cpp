#include "levelscreen.hpp"
#include "map/map.hpp"

LevelScreen::LevelScreen() : tileset(nullptr), map(nullptr)
{}

LevelScreen::~LevelScreen()
{
    if(tileset)
    {
        delete tileset;
        tileset = nullptr;
    }
    if(map)
    {
        delete map;
        map = nullptr;
    }
}

void LevelScreen::onStart(const GameState &gameState, const Window &window)
{
    tileset = new Tileset(gameState.getResourceFolderPath());
    map = new Map(window, gameState.getResourceFolderPath(), Const::MAP_1, tileset);
}

void LevelScreen::onUpdate(GameState &gameState, unsigned int deltaTime)
{}

void LevelScreen::onEvent(GameState &gameState, const SDL_Event &event)
{}

void LevelScreen::onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState)
{}

void LevelScreen::onDraw(const Window &window)
{
    map->draw(window);
}
