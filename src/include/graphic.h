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
    uint8_t         bg_r;               // Background color...
    uint8_t         bg_g;
    uint8_t         bg_b;
    uint8_t         fg_r;               // Foreground color...
    uint8_t         fg_g;
    uint8_t         fg_b;
    uint16_t        margin_t;           // Margins...
    uint16_t        margin_b;
    uint16_t        margin_l;
    uint16_t        margin_r;
    uint16_t        ln_sp;              // Line space
    SDL_Surface     *draw_surf;         // SDL surface
    TTF_Font        *raw_fnt;           // SDL TTF font
} GraphSt;

/*
 * Enum type listing all supported fonts.
 */
typedef enum __FNT__ {
    FNT_ATI,
    FNT_IBM
} Fnt;

/*
 * Initialize a GraphSt.
 */
void init_graph_st(GraphSt *graph_st);

/*
 * Load a font with a given pt size.
 */
void ld_fnt(GraphSt *graph_st, Fnt fnt, uint16_t pt, ErrSt *err_st);

/*
 * Quit the SDL graphics subsystem.
 */
void quit_graphics(GraphSt *graph_st);

#endif
