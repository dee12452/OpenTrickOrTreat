//
// Created by dee12452 on 5/24/23.
//

#ifndef __vita__

#include "Compat.h"
#include "Util.h"

int Compat::getWindowFlags() {
    return SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
}

double Compat::getPi() {
    return M_PI;
}

#endif