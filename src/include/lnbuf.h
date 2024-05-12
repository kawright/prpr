// Copyright (C) 2024  Kristoffer A. Wright

/*
 * lnbuf.h - Input line buffer
 */

#include <stdint.h>

#ifndef __LNBUF_H__
#define __LNBUF_H__

#define MAX_LN_LEN              127

/*
 * Fixed-length buffer used to store a line of user input.
 */
typedef char LnBuf [MAX_LN_LEN + 1];

/*
 * Initialize an LnBuf.
 */
void init_ln_buf(LnBuf ln_buf);

#endif
