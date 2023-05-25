//
// Created by dee12452 on 5/24/23.
//

#ifndef OPENTRICKORTREAT_WINDOW_H
#define OPENTRICKORTREAT_WINDOW_H

#include "Util.h"

class Window {
public:
    Window(const std::string& windowName, int windowFlags);
    Window(const std::string& windowName, int windowFlags, int x, int y, int w, int h);
    ~Window();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

    void clear(SDL_Color* color) const;
    void draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst) const;
    void present() const;
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif