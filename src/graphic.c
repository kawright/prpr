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
    graph_st->fg_b          = 0x00;
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

        case FNT_PLEX:
        data        = _binary_asset_plex_ttf_start;
        data_sz     = _binary_asset_plex_ttf_end - _binary_asset_plex_ttf_start;
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
    if (graph_st->raw_fnt == NULL) {
        throw (err_st, ERR_EXTERN, "Could not initialize font");
        return;
    }
}

void draw_ch_mat(GraphSt *graph_st, ChMat *ch_mat, ErrSt *err_st) {
    SDL_Surface     *ln_surf;
    char            ln [MAX_CH_MAT_COLS + 1];
    SDL_Color       fg = {graph_st->fg_r, graph_st->fg_g, graph_st->fg_b};
    SDL_Rect        blit_pos;

    if (graph_st->draw_surf != NULL) {
        SDL_FreeSurface(graph_st->draw_surf);
    }

    // Render a test line so we can get the dimensions and use to calc final dimensions
    ln[ch_mat->sz_cols] = '\0';
    for (int i = 0; i < ch_mat->sz_cols; i++) {
        ln[i] = 'X';
    }
    ln_surf = TTF_RenderText_Solid(graph_st->raw_fnt, ln, fg);
    if (ln_surf == NULL) {
        throw(err_st, ERR_EXTERN, "Could not render text '%s'", ln);
        return;
    }
    
    // Create the final surface
    uint16_t width = ln_surf->w + graph_st->margin_l + graph_st->margin_r;
    uint16_t height = ((ln_surf->h + graph_st->ln_sp) * ch_mat->sz_rows) + graph_st->margin_t + graph_st->margin_b;
    graph_st->draw_surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (graph_st->draw_surf == NULL) {
        throw(err_st, ERR_EXTERN, "Could not render character matrix surface");
        SDL_FreeSurface(ln_surf);
        return;
    }
    SDL_FillRect(graph_st->draw_surf, NULL, SDL_MapRGB(graph_st->draw_surf->format, graph_st->bg_r, graph_st->bg_g,
        graph_st->bg_b));
    
    // Render lines and blit onto the final surface
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        SDL_FreeSurface(ln_surf);
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            ln[x] = ch_mat->data[y][x];
        }
        ln_surf = TTF_RenderText_Solid(graph_st->raw_fnt, ln, fg);
        if (ln_surf == NULL) {
            throw(err_st, ERR_EXTERN, "Could not render text '%s'", ln);
            return;
        }
        blit_pos.x = graph_st->margin_l;
        blit_pos.y = graph_st->margin_t + (y * (ln_surf->h + graph_st->ln_sp));    
        blit_pos.h = ln_surf->h;
        blit_pos.w = ln_surf->w;
        if (SDL_BlitSurface(ln_surf, NULL, graph_st->draw_surf, &blit_pos) != 0) {
            throw(err_st, ERR_EXTERN, "Could not blit text");
            SDL_FreeSurface(ln_surf);
            SDL_FreeSurface(graph_st->draw_surf);
            graph_st->draw_surf = NULL;
            return;
        }
    }
    SDL_FreeSurface(ln_surf);
}

void sv_png(GraphSt *graph_st, char *fname, ErrSt *err_st) {
    if (IMG_SavePNG(graph_st->draw_surf, fname) == -1) throw(err_st, ERR_EXTERN, "Could not save draw surface to png");
}
