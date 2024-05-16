// Copyright (C) 2024  Kristoffer A. Wright

/*
 * graphic.c - Graphics Routines
 */

#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "asset.h"
#include "err.h"
#include "graphic.h"

void init_graph_st(GraphSt *graph_st) {
    graph_st->bg_r          = 0xff;
    graph_st->bg_g          = 0xff;
    graph_st->bg_b          = 0xff;
    graph_st->fg_r          = 0x00;
    graph_st->fg_g          = 0x00;
    graph_st->fg_g          = 0x00;
    graph_st->margin_t      = 8;
    graph_st->margin_b      = 8;
    graph_st->margin_l      = 8;
    graph_st->margin_r      = 8;
    graph_st->ln_sp         = 4;
    graph_st->draw_surf     = NULL;
    graph_st->raw_fnt       = NULL;  
}

void quit_graphics(GraphSt *graph_st) {
    if (graph_st->raw_fnt != NULL) {
        TTF_CloseFont(graph_st->raw_fnt);
    }
    SDL_Quit();
}

void ld_fnt(GraphSt *graph_st, Fnt fnt, uint16_t pt, ErrSt *err_st) {
    if (graph_st->raw_fnt != NULL) {
        TTF_CloseFont(graph_st->raw_fnt);
    }
    char        *data       = NULL;
    uint64_t    data_sz     = 0;
    switch (fnt) {
        case FNT_ATI:
        data        = _binary_asset_ati_9x14_ttf_start;
        data_sz     = _binary_asset_ati_9x14_ttf_end - _binary_asset_ati_9x14_ttf_start;
        break;

        case FNT_IBM:
        data        = _binary_asset_ibm_iso8_ttf_start;
        data_sz     = _binary_asset_ibm_iso8_ttf_end - _binary_asset_ibm_iso8_ttf_start;
        break;
        
        default:
        data        = _binary_asset_ati_9x14_ttf_start;
        data_sz     = _binary_asset_ati_9x14_ttf_end - _binary_asset_ati_9x14_ttf_start;
        break;
    }

    SDL_RWops *fp = SDL_RWFromConstMem(data, data_sz);
    if (fp == NULL) {
        throw(err_st, ERR_EXTERN, "Could not load font data");
        return;
    }
    graph_st->raw_fnt = TTF_OpenFontRW(fp, SDL_TRUE, (int) pt);
    if (graph_st->raw_fnt) {
        throw (err_st, ERR_EXTERN, "Could not initialize font");
        return;
    }
}
