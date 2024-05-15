// Copyright (C) 2024  Kristoffer A. Wright

/*
 * graphic.h - Graphics Routines
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>

#include "err.h"

/*
 * Initalize the SDL graphics subsystem. Must be called from main. Throws ERR_EXTERN if SDL reports an error.
 */
#define INIT_GRAPHICS();                                                                                    \
    if (SDL_Init(SDL_INIT_VIDEO) < 0) throw(&err_st, ERR_EXTERN, "Could not initialize SDL");

/*
 * Struct type which stores the state related to graphics rendering.
 */
typedef struct __GRAPH_ST__ {
    uint8_t         bg_r;
    uint8_t         bg_g;
    uint8_t         bg_b;
    uint8_t         fg_r;
    uint8_t         fg_g;
    uint8_t         fg_b;
    uint16_t        margin_t;
    uint16_t        margin_b;
    uint16_t        margin_l;
    uint16_t        margin_r;
    SDL_Surface     *draw_surf;
    TTF_Font        *fnt;
} GraphSt;

/*
 * Initialize a GraphSt.
 */
void init_graph_st(GraphSt *graph_st);

/*
 * Quit the SDL graphics subsystem.
 */
void quit_graphics();

#endif
