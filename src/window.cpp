#include "window.hpp"

Window::Window()
{
    init();
}

Window::Window(const Window & /*otherWindow*/) : Window()
{
}

Window& Window::operator=(const Window & /*otherWindow*/)
{
    deinit();
    init();
    return *this;
}

Window::~Window()
{
    deinit();
}

void Window::setTargetTexture(SDL_Texture *target) const
{
    Util::sdlFuncCheck(SDL_SetRenderTarget(sdlRenderer, target), "SDL_SetRenderTarget");
}

void Window::resetTargetTexture() const
{
    setTargetTexture(nullptr);
}

void Window::clear() const
{
    clear(Color::BLACK);
}

void Window::clear(SDL_Texture *texture) const
{
    clear(texture, Color::BLACK);
}

void Window::clear(const SDL_Color &color) const
{
    Util::sdlFuncCheck(SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a), "SDL_SetRenderDrawColor");
    Util::sdlFuncCheck(SDL_RenderClear(sdlRenderer), "SDL_RenderClear");
}

void Window::clear(SDL_Texture *texture, const SDL_Color &color) const
{
    Util::sdlFuncCheck(SDL_SetRenderTarget(sdlRenderer, texture), "SDL_SetRenderTarget");
    Util::sdlFuncCheck(SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a), "SDL_SetRenderDrawColor");
    Util::sdlFuncCheck(SDL_RenderClear(sdlRenderer), "SDL_RenderClear");
    Util::sdlFuncCheck(SDL_SetRenderTarget(sdlRenderer, nullptr), "SDL_SetRenderTarget");
}

void Window::draw(SDL_Texture *sdlTexture, const SDL_Rect &srcRect, const SDL_Rect &dstRect) const
{
    const SDL_Rect *sourceRect = &srcRect;
    if(srcRect.w == 0 && srcRect.h == 0)
    {
        sourceRect = nullptr;
    }
    Util::sdlFuncCheck(SDL_RenderCopy(sdlRenderer, sdlTexture, sourceRect, &dstRect), "SDL_RenderCopy");
}

void Window::draw(SDL_Texture *sdlTexture, const SDL_Rect &srcRect) const
{
    const SDL_Rect *sourceRect = &srcRect;
    if(srcRect.w == 0 && srcRect.h == 0)
    {
        sourceRect = nullptr;
    }
    Util::sdlFuncCheck(SDL_RenderCopy(sdlRenderer, sdlTexture, sourceRect, nullptr), "SDL_RenderCopy");
}

void Window::draw(SDL_Texture *sdlTexture) const
{
    Util::sdlFuncCheck(SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr), "SDL_RenderCopy");
}

void Window::render() const
{
    SDL_RenderPresent(sdlRenderer);
}

SDL_Renderer * Window::getSdlRenderer() const
{
    return sdlRenderer;
}

SDL_Texture * Window::createTexture(int w, int h) const
{
    return SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
}

SDL_Texture * Window::createTexture(int w, int h, const SDL_Color &baseColor) const
{
    SDL_Texture *texture = createTexture(w, h);
    setTargetTexture(texture);
    if(baseColor.a == 0)
    {
        Util::sdlFuncCheck(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND), "SDL_SetTextureBlendMode");
        Util::sdlFuncCheck(SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_NONE), "SDL_SetRenderDrawBlendMode");
        Util::sdlFuncCheck(SDL_SetRenderDrawColor(sdlRenderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a), "SDL_SetRenderDrawColor");
        Util::sdlFuncCheck(SDL_RenderFillRect(sdlRenderer, nullptr), "SDL_RenderFillRect");
        Util::sdlFuncCheck(SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND), "SDL_SetRenderDrawBlendMode");
    }
    else
    {
        setTargetTexture(texture);
        clear(baseColor);
    }
    resetTargetTexture();
    return texture;
}

void Window::init()
{
    sdlWindow = SDL_CreateWindow(
            "Open Trick Or Treat"
            , 0
            , 0
            , Const::DEFAULT_WINDOW_WIDTH
            , Const::DEFAULT_WINDOW_HEIGHT
            , SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(!sdlWindow)
    {
        Util::criticalSdlError("Failed to create SDL Window");
    }

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(!sdlRenderer)
    {
        Util::criticalSdlError("Failed to create SDL Renderer");
    }
    
    SDL_RenderSetLogicalSize(sdlRenderer, Const::DEFAULT_WINDOW_WIDTH, Const::DEFAULT_WINDOW_HEIGHT);
    SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::deinit()
{
    if(sdlRenderer)
    {
        SDL_DestroyRenderer(sdlRenderer);
    }
    if(sdlWindow)
    {
        SDL_DestroyWindow(sdlWindow);
    }
}
