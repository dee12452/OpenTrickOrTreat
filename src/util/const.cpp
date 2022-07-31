#include "const.hpp"

const unsigned int Const::FPS_CAP_MILLIS = 1000/60;
const char * const Const::DATA_FOLDER_PATH = "data/";
const char * const Const::TEXTURES_FOLDER_PATH = "textures/";
const char * const Const::FONTS_FOLDER_PATH = "fonts/";
const char * const Const::TILESETS_FOLDER_PATH = "tilesets/";
const char * const Const::MAPS_FOLDER_PATH = "maps/";
const int Const::DEFAULT_FONT_PT_SIZE = 20;
const float Const::DEFAULT_PLAYER_SPEED = 0.15f;

const char * const Const::IMAGE_CHARACTERS_SKELETON = "characters_skeleton.png";
const char * const Const::IMAGE_CHARACTERS_VAMPIRE = "character_vampire.png";
const char * const Const::IMAGE_CHARACTERS_MONSTER = "characters_monster.png";
const char * const Const::IMAGE_CHARACTERS_WITCH = "characters_witch.png";
const char * const Const::IMAGE_CHARACTERS_CREATURE = "characters_creature.png";
const char * const Const::IMAGE_TILESET = "tileset.png";
const char * const Const::IMAGE_MISC = "misc.png";

const char * const Const::FONT_TYPEWRITER = "veteran_typewriter.ttf";

const char * const Const::MAP_1 = "map_1.json";
const char * const Const::TILESET_1 = "tileset_1.json";

const int Const::DEFAULT_WINDOW_WIDTH = 800;
const int Const::DEFAULT_WINDOW_HEIGHT = 600;
const SDL_Rect Const::EMPTY_RECT = {0, 0, 0, 0};

const SDL_Color Color::BLACK = {0, 0, 0, 255}; 
const SDL_Color Color::WHITE = {255, 255, 255, 255}; 
const SDL_Color Color::TRANSPARENT = {0, 0, 0, 0}; 
