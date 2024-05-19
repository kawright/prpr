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
