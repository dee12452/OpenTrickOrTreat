#ifndef _OPEN_TOT_TEXT_SPRITE_HPP_
#define _OPEN_TOT_TEXT_SPRITE_HPP_

#include "sprite.hpp"

class TextSprite : public Sprite
{
public:
    TextSprite(
            const Window &window
            , const std::string &text
            , const std::string &font
            , const SDL_Color &color);
    TextSprite(
            const Window &window
            , const std::string &text
            , const std::string &font
            , const SDL_Color &color
            , const SDL_Rect &sourceRect
            , const SDL_Rect &destinationRect);
    ~TextSprite() override;

    virtual void draw(const Window &window) const override;

    const std::string & getText() const;
    void setText(const Window &window, const std::string &newText);
    
    const std::string & getFont() const;
    void setFont(const Window &window, const std::string &newFont);

    const SDL_Color & getColor() const;
    void setColor(const Window &window, const SDL_Color &newColor);

private:
    SDL_Texture *createTextTexture(
            SDL_Renderer *renderer
            , const std::string &text
            , TTF_Font *font
            , const SDL_Color &color) const;

    std::string text;
    std::string font;
    SDL_Color color;
};

#endif
