#include "textsprite.hpp"
#include "fontmanager.hpp"

TextSprite::TextSprite() :
    text(), font(), color({0,0,0,0})
{}

TextSprite::TextSprite(
        const Window &window
        , const std::string &text
        , const std::string &font
        , const SDL_Color &color) :
    TextSprite(window, text, font, color, {0,0,0,0}, {0,0,0,0})
{}

TextSprite::TextSprite(
        const Window &window
        , const std::string &text
        , const std::string &font
        , const SDL_Color &color
        , const SDL_Rect &sourceRect
        , const SDL_Rect &destinationRect)
    : Sprite(nullptr, sourceRect, destinationRect)
      , text(text)
      , font(font)
      , color(color)
{
    setSdlTexture(createTextTexture(
                window.getSdlRenderer()
                , text
                , FontManager::getInstance()->getFont(font)
                , color));
}

TextSprite::TextSprite(const TextSprite &textSprite) :
    text(textSprite.text), font(textSprite.font), color(textSprite.color)
{
    setX(textSprite.getX());
    setY(textSprite.getY());
    setWidth(textSprite.getWidth());
    setHeight(textSprite.getHeight());
    setSdlTexture(nullptr);
}

TextSprite& TextSprite::operator=(const TextSprite &textSprite)
{
    setX(textSprite.getX());
    setY(textSprite.getY());
    setWidth(textSprite.getWidth());
    setHeight(textSprite.getHeight());
    text = textSprite.text;
    font = textSprite.font;
    color = textSprite.color;
    if(getSdlTexture())
    {
        SDL_DestroyTexture(getSdlTexture());
    }
    setSdlTexture(nullptr);
    return *this;
}

TextSprite::~TextSprite()
{
    if(getSdlTexture())
    {
        SDL_DestroyTexture(getSdlTexture());
    }
    setSdlTexture(nullptr);
}

void TextSprite::draw(const Window &window)
{
    if(!getSdlTexture())
    {
        setSdlTexture(createTextTexture(
                window.getSdlRenderer()
                , text
                , FontManager::getInstance()->getFont(font)
                , color));
    }
    Sprite::draw(window);
}

const std::string & TextSprite::getText() const
{
    return text;
}

void TextSprite::setText(const Window &window, const std::string &newText)
{
    text = newText;
    setSdlTexture(createTextTexture(
            window.getSdlRenderer()
            , text
            , FontManager::getInstance()->getFont(font)
            , color));
}

const std::string & TextSprite::getFont() const
{
    return font;
}

void TextSprite::setFont(const Window &window, const std::string &newFont)
{
    font = newFont;
    setSdlTexture(createTextTexture(
            window.getSdlRenderer()
            , text
            , FontManager::getInstance()->getFont(font)
            , color));
}

const SDL_Color & TextSprite::getColor() const
{
    return color;
}

void TextSprite::setColor(const Window &window, const SDL_Color &newColor)
{
    color = newColor;
    setSdlTexture(createTextTexture(
            window.getSdlRenderer()
            , text
            , FontManager::getInstance()->getFont(font)
            , color));
}

SDL_Texture * TextSprite::createTextTexture(
        SDL_Renderer *renderer
        , const std::string &text
        , TTF_Font *font
        , const SDL_Color &color) const
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return textTexture;
}

