#include "Window.h"

Window::Window(const std::string& windowName, int windowFlags)
    : Window(
        windowName,
        windowFlags,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600) {}

Window::Window(const std::string &windowName, int windowFlags, int x, int y, int w, int h) {
    m_window = SDL_CreateWindow(windowName.c_str(), x, y, w, h, windowFlags);
    if(m_window == nullptr) {
        const std::string message = "Unable to create a game window: ";
        Logger::error(message + SDL_GetError());
        exit(-1);
    }

    const int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);
    if(m_renderer == nullptr) {
        const std::string message = "Unable to create a game window renderer: ";
        Logger::error(message + SDL_GetError());
        exit(-1);
    }
}

Window::~Window() {
    if(m_renderer) SDL_DestroyRenderer(m_renderer);
    if(m_window) SDL_DestroyWindow(m_window);
}

SDL_Window* Window::getWindow() const {
    return m_window;
}

SDL_Renderer* Window::getRenderer() const {
    return m_renderer;
}

void Window::clear(SDL_Color* color) const {
    if(color != nullptr) {
        SDL_SetRenderDrawColor(m_renderer, color->r, color->g, color->b, color->a);
    } else {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    }

    if(SDL_RenderClear(m_renderer) < 0) {
        const std::string message = "Unable to clear the SDL2 renderer: ";
        Logger::error(message + SDL_GetError());
        exit(-1);
    }
}

void Window::draw(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst) const {
    if(texture == nullptr) {
        Logger::warn("Attempted to draw a NULL texture.");
        return;
    }

    if(SDL_RenderCopy(m_renderer, texture, src, dst) < 0) {
        const std::string message = "Unable to draw an SDL2 texture: ";
        Logger::error(message + SDL_GetError());
        exit(-1);
    }
}

void Window::present() const {
    SDL_RenderPresent(m_renderer);
}
