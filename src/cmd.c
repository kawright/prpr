// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmd.c - Commands
 */

#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "chmat.h"
#include "err.h"
#include "graphic.h"
#include "fdback.h"

void cmd_quit() {
    exit(0);
}

void cmd_dim(ChMat *ch_mat, uint16_t cols, uint16_t rows, ErrSt *err_st) {
    dim_ch_mat(ch_mat, cols, rows, err_st);
    if (err_st->code == ERR_RANGE) {
        fdback_err();
        init_err_st(err_st);
        return;
    }
    if (is_err_thrown(err_st)) return;
    ch_mat->sz_cols = cols;
    ch_mat->sz_rows = rows;
    fdback_ok();
    return;
}

void cmd_fill(ChMat *ch_mat, char fill_ch) {
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            ch_mat->data[y][x] = fill_ch;
        }
    }
    fdback_ok();
}

void cmd_print(ChMat *ch_mat) {
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            putc(ch_mat->data[y][x], stdout);
        }
        putc('\n', stdout);
    }
    fdback_ok();
}

void cmd_txt(ChMat *ch_mat, char *fname) {
    FILE *fp = fopen(fname, "w");
    if (fp == NULL) {
        fdback_err();
        return;
    }
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            putc(ch_mat->data[y][x], fp);
        }
        putc('\n', fp);
    }
    fclose(fp);
    fdback_ok();
    
}

void cmd_quitgraph(GraphSt *graph_st) {
    quit_graphics(graph_st);
    fdback_ok();
}


void cmd_fdback(bool val) {
    fdback_set(val);
    fdback_ok();
}

void cmd_pngdraw(GraphSt *graph_st, ChMat *ch_mat, ErrSt *err_st) {
    draw_ch_mat(graph_st, ch_mat, err_st);
    if (is_err_thrown(err_st)) {
        fdback_err();
        init_err_st(err_st);
        return;
    }
    fdback_ok();
}


void cmd_pngsv(GraphSt *graph_st, char *fname, ErrSt *err_st) {
    sv_png(graph_st, fname, err_st);
    if (is_err_thrown(err_st)) {
        fdback_err();
        init_err_st(err_st);
        return;
    }
    fdback_ok();
}

void cmd_putl(ChMat *ch_mat, uint16_t x, uint16_t y, char *str) {
    if (y >= ch_mat->sz_rows) {
        fdback_err();
        return;
    }
    for (int i = 0; i < strlen(str); i++) {
        if (x + i >= ch_mat->sz_cols) {
            fdback_err();
            return;
        }
        ch_mat->data[y][x + i] = str[i];
    }
    fdback_ok();
}

void cmd_putr(ChMat *ch_mat, uint16_t x, uint16_t y, char *str) {
    if (y >= ch_mat->sz_rows) {
        fdback_err();
        return;
    }
    for (int i = strlen(str) - 1; i >= 0; i--) {
        
        if (x + i - strlen(str) >= ch_mat->sz_cols) {
            fdback_err();
            return;
        }
        if (x + i - strlen(str) < 0) {
            fdback_err();
            return;
        }
        ch_mat->data[y][x + i - strlen(str)] = str[i];
    }
    fdback_ok();
}

void cmd_putc(ChMat *ch_mat, uint16_t ln, char *str) {
    if (strlen(str) > ch_mat->sz_cols) {
        fdback_err();
        return;
    }
    for (int i = 0; i < strlen(str); i++) {
        ch_mat->data[ln][ch_mat->sz_cols/2 - strlen(str)/2 + i] = str[i];
    }
    fdback_ok();
}

void cmd_hrule(ChMat *ch_mat, uint16_t ln, char *ch) {
    if (ln >= ch_mat->sz_rows) {
        fdback_err();
        return;
    }
    for (int i = 0; i < ch_mat->sz_cols; i++) {
        ch_mat->data[ln][i] = ch[0];
    }
    fdback_ok();
}

void cmd_fbox(ChMat *ch_mat, uint16_t uplx, uint16_t uply, uint16_t botrx, uint16_t botry, char *ch) {
    if (
            (uplx >= ch_mat->sz_cols)       ||
            (botrx >= ch_mat->sz_cols)      ||
            (uply >= ch_mat->sz_rows)       ||
            (botry >= ch_mat->sz_rows)      ||
            (uplx >= botrx)                 ||
            (uply >= botry)) {
        fdback_err();
        return;
    }
    for (int y = uply; y <= botry; y++) {
        for (int x = uplx; x <= botrx; x++) {
            ch_mat->data[y][x] = ch[0];
        }
    }
    fdback_ok();
}

void cmd_box(ChMat *ch_mat, uint16_t uplx, uint16_t uply, uint16_t botrx, uint16_t botry, char *horiz, char *vert,
        char *crnr) {
    if (
            (uplx >= ch_mat->sz_cols)       ||
            (botrx >= ch_mat->sz_cols)      ||
            (uply >= ch_mat->sz_rows)       ||
            (botry >= ch_mat->sz_rows)      ||
            (uplx >= botrx)                 ||
            (uply >= botry)) {
        fdback_err();
        return;
    }

    // Corners
    ch_mat->data[uply][uplx] = crnr[0];
    ch_mat->data[uply][botrx] = crnr[0];
    ch_mat->data[botry][uplx] = crnr[0];
    ch_mat->data[botry][botrx] = crnr[0];
    
    // Horizontals
    for (int x = uplx + 1; x < botrx; x++) {
        ch_mat->data[uply][x] = horiz[0];
        ch_mat->data[botry][x] = horiz[0];
    } 

    // Verticals
    for (int y = uply + 1; y < botry; y++) {
        ch_mat->data[y][uplx] = vert[0];
        ch_mat->data[y][botrx] = vert[0];
    }
    fdback_ok();
}

void cmd_fnt(GraphSt *graph_st, char *fnt, uint16_t pt, ErrSt *err_st) {
    Fnt fnt_real;
    if (strcmp(fnt, "IBM") == 0) {
        fnt_real = FNT_IBM; 
    } else if (strcmp(fnt, "ATI") == 0) {
        fnt_real = FNT_ATI;
    } else if (strcmp(fnt, "PLEX") == 0) {
        fnt_real = FNT_PLEX;
    } else {
        fdback_err();
        return;
    }
    ld_fnt(graph_st, fnt_real, pt, err_st);
    if (is_err_thrown(err_st)) {
        fdback_err();
        init_err_st(err_st);
        return;
    }
    fdback_ok();
}

void cmd_bg(GraphSt *graph_st, uint8_t r, uint8_t g, uint8_t b) {
    graph_st->bg_r = r;
    graph_st->bg_g = g;
    graph_st->bg_b = b;
    fdback_ok();
}

void cmd_fg(GraphSt *graph_st, uint8_t r, uint8_t g, uint8_t b) {
    graph_st->fg_r = r;
    graph_st->fg_g = g;
    graph_st->fg_b = b;
    fdback_ok();
}

void cmd_cp(ChMat *ch_mat, uint16_t x, uint16_t y, char *fname, uint16_t start, uint16_t lns) {
    if (
            (x >= ch_mat->sz_cols) ||
            (y >= ch_mat->sz_rows)) {
        fdback_err();
        return;
    }
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        fdback_err();
        return;
    }
    char ln_buf[512];
    for (int i = 0; i < start; i++) {
        if (!(fgets(ln_buf, 511, fp))) {
            fclose(fp);
            fdback_err();
            return;
        };
    }
    for (int j = 0; j < lns; j++) {
        if (y + j >= ch_mat->sz_rows) break;
        if (!(fgets(ln_buf, 511, fp))) {
            fclose(fp);
            fdback_ok();
            return;
        }
        for (int i = 0; i < strlen(ln_buf) - 1; i++) {
            if (x + i >= ch_mat->sz_cols) break;
            ch_mat->data[y + j][x + i] = ln_buf[i]; 
        }
    } 
    fclose(fp);
    fdback_ok();
}

void cmd_lnsp(GraphSt *graph_st, uint16_t lnsp) {
    graph_st->ln_sp = lnsp;
    fdback_ok();
}

void cmd_echo(char *msg) {
    printf("%s\n", msg);
    fdback_ok();
}
