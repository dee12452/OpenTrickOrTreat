#ifndef _OPEN_TOT_PLAY_SCREEN_HPP_
#define _OPEN_TOT_PLAY_SCREEN_HPP_

#include "screen.hpp"
#include "playersprite.hpp"

class PlayScreen : public Screen
{
public:
    PlayScreen();
    ~PlayScreen() override;

protected:
    void onStart(const GameState &gameState, const Window &window) override;
    void onUpdate(GameState &gameState, unsigned int deltaTime) override;
    void onEvent(GameState &gameState, const SDL_Event &event) override;
    void onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState) override;
    void onDraw(const Window &window) override;

private:
    void generateConsumables();
    void drawCamera(const Window &window);

    Map *currentMap;
    Tileset *tileset;
    PlayerSprite *player;
    std::vector<MapSprite *> mapSprites;
    bool hasDrawn;
};

#endif
