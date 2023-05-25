//
// Created by dee12452 on 5/24/23.
//

#ifndef OPENTRICKORTREAT_GAME_H
#define OPENTRICKORTREAT_GAME_H

#include "Window.h"

class Game {
public:
    explicit Game(const std::string& name);
    ~Game();

    void run();

private:
    static int TARGET_FRAMES_PER_SECOND;
    static int TICKS_PER_SECOND;

    std::string m_gameName;
    int m_tickTime;
    bool m_running;

    void render(const Window& window);
    void update(int tickMs);
    void tick();

    // TODO: Get rid of
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* helloWorldTexture;
};

#endif