// Copyright (C) 2024  Kristoffer A. Wright

/*
 * main.c - Entry point
 */

#include <stdio.h>
#include <string.h>

#include "cmdbuf.h"
#include "err.h"
#include "lnbuf.h"

int main(int argc, char *argv[]) {
    ErrSt   err_st;
    LnBuf   ln_buf;
    CmdBuf  cmd_buf;
    init_err_st(&err_st);
    init_ln_buf(ln_buf);
    init_cmd_buf(&cmd_buf);

    while (strcmp(ln_buf, "quit\n") != 0) {
        printf("> ");
        fgets(ln_buf, MAX_LN_LEN, stdin);
    }
    
    return err_st.code;
}
