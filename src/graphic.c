// Copyright (C) 2024  Kristoffer A. Wright

/*
 * graphic.c - Graphics Routines
 */

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "err.h"
#include "graphic.h"

void init_graphics(ErrSt *err_st) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) throw(err_st, ERR_EXTERN, "Could not initialize SDL");
}

void quit_graphics() {
    SDL_Quit();
}
