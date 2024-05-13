// Copyright (C) 2024  Kristoffer A. Wright

/*
 * chmat.c - Character Matrix
 */

#include "chmat.h"

void init_ch_mat(ChMat *ch_mat) {
    ch_mat->sz_cols = 0;
    ch_mat->sz_rows = 0;
    for (int y = 0; y < MAX_CH_MAT_ROWS; y++) {
        for (int x = 0; x < MAX_CH_MAT_COLS; x++) {
            ch_mat->data[y][x] = 0;
        }
    }
}


void dim_ch_mat(ChMat *ch_mat, uint16_t sz_cols, uint16_t sz_rows, ErrSt *err_st) {
    if (sz_cols > MAX_CH_MAT_COLS) {
        throw(err_st, ERR_RANGE, "Cannot exceed %d columns", MAX_CH_MAT_COLS);
        return;
    }
    if (sz_rows > MAX_CH_MAT_ROWS) {
        throw(err_st, ERR_RANGE, "Cannot exceed %d rows", MAX_CH_MAT_ROWS);
        return;
    }
    if (sz_cols <= 0) {
        throw(err_st, ERR_RANGE, "Columns must be positive");
        return;
    }
    if (sz_rows <= 0) {
        throw(err_st, ERR_RANGE, "Rows must be positive");
        return; 
    }
        
    for (int y = sz_rows; y < MAX_CH_MAT_ROWS; y++) {
        for (int x = sz_cols; x < MAX_CH_MAT_COLS; x++) {
            ch_mat->data[y][x] = 0;
        }
    }
}
