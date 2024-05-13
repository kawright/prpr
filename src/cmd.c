// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmd.c - Commands
 */

#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "chmat.h"
#include "err.h"

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
    printf("OK\n");
    return;
}
