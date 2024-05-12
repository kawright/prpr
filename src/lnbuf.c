// Copyright (C) 2024  Kristoffer A. Wright

/*
 * lnbuf.c - Input line buffer
 */

#include "lnbuf.h"


void init_ln_buf(LnBuf ln_buf) {
    for (int i=0; i<MAX_LN_LEN; i++) {
        ln_buf[i] = 0;
    }
}
