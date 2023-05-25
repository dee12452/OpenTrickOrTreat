#include "Game.h"

int Game::TARGET_FRAMES_PER_SECOND = 60;
int Game::TICKS_PER_SECOND = 20;

Game::Game(const std::string& gameName) : m_gameName(gameName), m_running(true), m_tickTime(0) {
    font = nullptr;
    surface = nullptr;
    helloWorldTexture = nullptr;
}

Game::~Game() {
    if(font) TTF_CloseFont(font);
    if(surface) SDL_FreeSurface(surface);
    if(helloWorldTexture) SDL_DestroyTexture(helloWorldTexture);
}

void Game::run() {
    Window window(m_gameName, Compat::getWindowFlags());
    const std::string assetsPath = std::string(SDL_GetBasePath()) + "assets/";
    const std::string fontFilePath = assetsPath + "opensans.ttf";
    font = TTF_OpenFont(fontFilePath.c_str(), 20);
    surface = TTF_RenderText_Solid(font, "Hello World!", {255, 255, 255, 255});
    helloWorldTexture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);

    const int targetFrameMs = 1000 / Game::TARGET_FRAMES_PER_SECOND;
    const int tickMs = 1000 / Game::TICKS_PER_SECOND;

    Logger::debug("Starting game loop.");
    Uint64 loopStartTime = SDL_GetTicks64();
    Uint64 loopEndTime;
    while(m_running) {
        render(window);
        update(tickMs);

        loopEndTime = SDL_GetTicks64();
        const Uint64 gameLoopTime = loopEndTime - loopStartTime;
        loopStartTime = SDL_GetTicks64();
        m_tickTime += static_cast<int>(gameLoopTime);
        if(gameLoopTime < targetFrameMs) {
            SDL_Delay(targetFrameMs - gameLoopTime);
        }
    }
    Logger::debug("Closing game loop.");
}

void Game::render(const Window& window) {
    window.clear(nullptr);
    window.draw(helloWorldTexture, nullptr, nullptr);
    window.present();
}

void Game::update(int tickMs) {
    // TODO: Handle event loop in compat
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_running = false;
                break;
            default:
                break;
        }
    }

    int ticks = 0;
    while(m_tickTime > tickMs) {
        m_tickTime -= tickMs;
        ticks++;
    }

    while(ticks > 0) {
        tick();
        ticks--;
    }
}

void Game::tick() {
}
