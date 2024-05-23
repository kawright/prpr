// Copyright (C) 2024  Kristoffer A. Wright

/*
 * chmat.h - Character Matrix
 */

#ifndef __CHMAT_H__
#define __CHMAT_H__

#include <stdint.h>

#include "err.h"

/*
 * Maximum number of columns allowed in a ChMat.
 */
#define MAX_CH_MAT_COLS         512

/*
 * Maximum number of rows allowed in a ChMat.
 */
#define MAX_CH_MAT_ROWS         256

/*
 * Struct type for storing a matrix of characters.
 */
typedef struct __CH_MAT__ {
    uint16_t        sz_cols;
    uint16_t        sz_rows;
    char            data[MAX_CH_MAT_ROWS][MAX_CH_MAT_COLS];
} ChMat;

/*
 * Initialize a ChMat.
 */
void init_ch_mat(ChMat *ch_mat);

/*
 * Set the dimensions of a ChMat. All values outside of the new range will be set to zero. Throws ERR_RANGE if sz_cols
 * or sz_rows exceeds maximum allowed values.
 */
void dim_ch_mat(ChMat *ch_mat, uint16_t sz_cols, uint16_t sz_rows, ErrSt *err_st);

#endif
