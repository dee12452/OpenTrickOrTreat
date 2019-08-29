#ifndef _OPEN_TOT_LAUNCH_SCREEN_HPP_
#define _OPEN_TOT_LAUNCH_SCREEN_HPP_

#include "screen.hpp"
#include "textsprite.hpp"
#include "animation/animationmanager.hpp"

class LaunchScreen : public Screen
{
private:
    static const char * const LOADING_TEXT;

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
    void loadAnimations();
    void loadNextTexture(const Window &window);

    std::string pathToResourceFolder;
    std::vector<std::string> texturesToLoad;
    std::vector<std::string> fontsToLoad;
    std::vector<std::string> animationsToLoad;
    TextSprite loadingText;
};

#endif
