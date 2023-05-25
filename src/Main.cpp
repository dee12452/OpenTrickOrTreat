#include "Util.h"
#include "Game.h"

int init();
void quit();

int main() {
	if(init() < 0) {
        return -1;
    }

    Game("OpenTrickOrTreat").run();

    quit();
	return 0;
}

int init() {
    int initResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);
    if(initResult < 0) {
        const std::string message = "SDL2 failed to initialize: ";
        Logger::error(message + SDL_GetError());
        return initResult;
    }

    initResult = IMG_Init(IMG_INIT_PNG);
    if(initResult < 0) {
        const std::string message = "SDL2 Image failed to initialize: ";
        Logger::error(message + IMG_GetError());
        return initResult;
    }

    initResult = TTF_Init();
    if(initResult < 0) {
        const std::string message = "SDL2 TTF failed to initialize: ";
        Logger::error(message + TTF_GetError());
        return initResult;
    }

    initResult = enet_initialize();
    if(initResult < 0) {
        const std::string message = "Enet failed to initialize.";
        Logger::error(message);
        return initResult;
    }

    return 0;
}

void quit() {
    enet_deinitialize();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
