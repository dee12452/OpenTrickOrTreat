#ifndef _OPEN_TOT_SPRITE_HPP_
#define _OPEN_TOT_SPRITE_HPP_

#include "window.hpp"

class Sprite
{
public:
    Sprite();
    Sprite(SDL_Texture *texture);
    Sprite(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destinationRect);
    virtual ~Sprite();
    
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    
    int getSourceX() const;
    int getSourceY() const;
    int getSourceWidth() const;
    int getSourceHeight() const;

    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    
    void setSourceX(int x);
    void setSourceY(int y);
    void setSourceWidth(int w);
    void setSourceHeight(int h);

    void center();

    virtual void draw(const Window &window) const;

    SDL_Rect getSourceRect() const;
    void setSourceRect(const SDL_Rect &rect);
    SDL_Rect getDestinationRect() const;
    void setDestinationRect(const SDL_Rect &rect);

    SDL_Texture * getSdlTexture() const;
    void setSdlTexture(SDL_Texture *newTexture);

private:
    SDL_Texture *sdlTexture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
};

#endif
