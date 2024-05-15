// Copyright (C) 2024  Kristoffer A. Wright

/*
 * graphic.h - Graphics Routines
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <stdbool.h>

#include "err.h"

/*
 * Initalize the SDL graphics subsystem. Must be called from main. Throws ERR_EXTERN if SDL reports an error.
 */
#define init_graphics();                                                                                    \
    if (SDL_Init(SDL_INIT_VIDEO) < 0) throw(&err_st, ERR_EXTERN, "Could not initialize SDL");
/*
 * Quit the SDL graphics subsystem.
 */
void quit_graphics();

#endif
