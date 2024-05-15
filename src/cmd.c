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

void cmd_quit() {
    exit(0);
}

void cmd_dim(ChMat *ch_mat, uint16_t cols, uint16_t rows, ErrSt *err_st) {
    dim_ch_mat(ch_mat, cols, rows, err_st);
    if (err_st->code == ERR_RANGE) {
        printf("ERR\n");
        init_err_st(err_st);
        return;
    }
    if (is_err_thrown(err_st)) return;
    ch_mat->sz_cols = cols;
    ch_mat->sz_rows = rows;
    printf("OK\n");
    return;
}

void cmd_fill(ChMat *ch_mat, char fill_ch) {
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            ch_mat->data[y][x] = fill_ch;
        }
    }
    printf("OK\n");
}

void cmd_print(ChMat *ch_mat) {
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            putc(ch_mat->data[y][x], stdout);
        }
        putc('\n', stdout);
    }
    printf("OK\n");
}

void cmd_txt(ChMat *ch_mat, char *fname) {
    FILE *fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("ERR\n");
        return;
    }
    for (int y = 0; y < ch_mat->sz_rows; y++) {
        for (int x = 0; x < ch_mat->sz_cols; x++) {
            putc(ch_mat->data[y][x], fp);
        }
        putc('\n', fp);
    }
    fclose(fp);
    printf("OK\n");
    
}

void cmd_quitgraph() {
    quit_graphics();
    printf("OK\n");    
}
