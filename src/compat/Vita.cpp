//
// Created by dee12452 on 5/24/23.
//

#ifdef __vita__

#include <SDL2/SDL.h>
#include "Util.h"

int Compat::getWindowFlags() {
    return SDL_WINDOW_FULLSCREEN;
}

double Compat::getPi() {
    const double pi = 3.14159265358979323846;
    return pi;
}

#endif
