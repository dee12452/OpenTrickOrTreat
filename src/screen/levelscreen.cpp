#include "levelscreen.hpp"
#include "map/map.hpp"
#include "sprite/playersprite.hpp"

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
{
    map->update(deltaTime);
}

void LevelScreen::onEvent(GameState &gameState, const SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                gameState.setState(State::STOP);
                return;
        
            case SDLK_SPACE:
                map->getPlayer()->doAction(map);
                break;
        }
        
    }
}

void LevelScreen::onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState)
{
    MapSprite *player = map->getPlayer();
    if(keyboardState[SDL_SCANCODE_UP])
    {
        player->stopX();
        player->setSpeedY(-Const::DEFAULT_PLAYER_SPEED);
    } 
    else if(keyboardState[SDL_SCANCODE_DOWN])
    {
        player->stopX();
        map->getPlayer()->setSpeedY(Const::DEFAULT_PLAYER_SPEED);
    }
    else if(keyboardState[SDL_SCANCODE_LEFT])
    {
        player->stopY();
        map->getPlayer()->setSpeedX(-Const::DEFAULT_PLAYER_SPEED);
    }
    else if(keyboardState[SDL_SCANCODE_RIGHT])
    {
        player->stopY();
        map->getPlayer()->setSpeedX(Const::DEFAULT_PLAYER_SPEED);
    }
    else
    {
        map->getPlayer()->stopX();
        map->getPlayer()->stopY();
    }
}

void LevelScreen::onDraw(const Window &window) const
{
    map->draw(window);
}
