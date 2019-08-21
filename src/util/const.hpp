#ifndef _OPEN_TOT_CONST_HPP_
#define _OPEN_TOT_CONST_HPP_

#include <SDL2/SDL_rect.h>

enum CostumeType {SKELETON = 0, WITCH = 1, MONSTER = 2, VAMPIRE = 3, FISH = 4};
enum MoveDirectionY {UP, DOWN, NONE_Y};
enum MoveDirectionX {LEFT, RIGHT, NONE_X};

namespace Const
{
    extern const unsigned int FPS_CAP_MILLIS;
    extern const char * const DATA_FOLDER_PATH;
    extern const char * const TEXTURES_FOLDER_PATH;
    extern const char * const FONTS_FOLDER_PATH;
    extern const char * const TILESETS_FOLDER_PATH;
    extern const char * const MAPS_FOLDER_PATH;
    extern const char * const ANIMATIONS_FOLDER_PATH;
    
    extern const int DEFAULT_FONT_PT_SIZE;
    extern const int DEFAULT_WINDOW_WIDTH;
    extern const int DEFAULT_WINDOW_HEIGHT;

    extern const char * const ANIMATION_CS_SKELETON;
    extern const char * const ANIMATION_CS_WITCH;
    extern const char * const ANIMATION_CS_MONSTER;
    extern const char * const ANIMATION_CS_VAMPIRE;
    extern const char * const ANIMATION_CS_FISH;
    extern const char * const ANIMATION_CANDY;
    extern const char * const ANIMATION_COIN;

    extern const char * const IMAGE_TOT_1;
    extern const char * const IMAGE_TOT_2;
    extern const char * const IMAGE_TOT_3;

    extern const char * const FONT_TYPEWRITER;

    extern const char * const MAP_1;
    
    extern const char * const TILESET_1;

    extern const SDL_Rect EMPTY_RECT;
}

namespace Color
{
    extern const SDL_Color BLACK; 
    extern const SDL_Color WHITE; 
    extern const SDL_Color TRANSPARENT; 
}

#endif
