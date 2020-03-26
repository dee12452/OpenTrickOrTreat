#ifndef _OPEN_TOT_WINDOW_HPP_
#define _OPEN_TOT_WINDOW_HPP_

#include "util/util.hpp"

class Window
{
public:
    Window();
    Window(const Window &otherWindow);
    Window& operator=(const Window &otherWindow);
    ~Window();

    void setTargetTexture(SDL_Texture *target) const;
    void resetTargetTexture() const;
    void clear() const;
    void clear(SDL_Texture *texture) const;
    void clear(const SDL_Color &color) const;
    void clear(SDL_Texture *texture, const SDL_Color &color) const;
    void draw(SDL_Texture *sdlTexture, const SDL_Rect &srcRect, const SDL_Rect &dstRect) const;
    void draw(SDL_Texture *sdlTexture, const SDL_Rect &srcRect) const;
    void render() const;

    SDL_Renderer * getSdlRenderer() const;
    SDL_Texture * createTexture(int w, int h) const;
    SDL_Texture * createTexture(int w, int h, const SDL_Color &baseColor) const;

private:
    void init();
    void deinit();

    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
};

#endif
