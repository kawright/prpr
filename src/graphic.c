// Copyright (C) 2024  Kristoffer A. Wright

/*
 * graphic.c - Graphics Routines
 */

#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "err.h"
#include "graphic.h"

void init_graph_st(GraphSt *graph_st) {
    graph_st->bg_r          = 0xff;
    graph_st->bg_g          = 0xff;
    graph_st->bg_b          = 0xff;
    graph_st->fg_r          = 0x00;
    graph_st->fg_g          = 0x00;
    graph_st->fg_g          = 0x00;
    graph_st->margin_t      = 0;
    graph_st->margin_b      = 0;
    graph_st->margin_l      = 0;
    graph_st->margin_r      = 0;
    graph_st->draw_surf     = NULL;
    graph_st->fnt           = NULL;  
}

void quit_graphics() {
    SDL_Quit();
}
