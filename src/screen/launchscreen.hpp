#ifndef _OPEN_TOT_LAUNCH_SCREEN_HPP_
#define _OPEN_TOT_LAUNCH_SCREEN_HPP_

#include "screen.hpp"
#include "sprite/textsprite.hpp"
#include "util/timer.hpp"

class LaunchScreen : public Screen
{
private:
    static const unsigned int LOAD_TIMER_DELAY; 
    static const char * const LOADING_TEXT;
    static const SDL_Rect LOADING_TEXT_DESTINATION_RECT;

public:
    LaunchScreen();
    ~LaunchScreen() override;

protected:
    void onStart(const GameState &gameState, const Window &window) override;
    void onUpdate(GameState &gameState, unsigned int deltaTime) override;
    void onEvent(GameState &gameState, const SDL_Event &event) override;
    void onKeyboardUpdate(GameState &gameState, const unsigned char *keyboardState) override;
    void onDraw(const Window &window) override;

private:
    void loadFonts();
    void loadNextTexture(const Window &window);

    std::string pathToResourceFolder;
    std::vector<std::string> texturesToLoad;
    std::vector<std::string> fontsToLoad;
    TextSprite loadingText;
    Timer loadTimer;
};

#endif
