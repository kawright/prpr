// Copyright (C) 2024  Kristoffer A. Wright

/*
 * err.c - Error handling
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"

void init_err_st(ErrSt *err_st) {
    err_st->code = ERR_OK;
    strcpy(err_st->msg, "");
}


void throw(ErrSt *err_st, ErrCode code, const char *msg, ...) {
    va_list args;
    va_start(args, msg);

    err_st->code = code;
    vsnprintf(err_st->msg, MAX_ERR_MSG_LEN, msg, args);

    va_end(args);
}

bool is_err_thrown(ErrSt *err_st) {
    return err_st->code != ERR_OK;
}


void panic(const ErrSt *err_st) {
    fprintf(stderr, "ERROR (0x%02x): %s\n", err_st->code, err_st->msg);
    exit(err_st->code);
}


void warning(const ErrSt *err_st) {
    fprintf(stderr, "WARNING (0x%02x): %s\n", err_st->code, err_st->msg);
}
