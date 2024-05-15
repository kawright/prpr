// Copyright (C) 2024  Kristoffer A. Wright

/*
 * graphic.c - Graphics Routines
 */

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "err.h"
#include "graphic.h"

void quit_graphics() {
    SDL_Quit();
}
