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
        init_cmd_buf(&cmd_buf);
        parse_cmd(&cmd_buf, ln_buf, &err_st);
        if (is_err_thrown(&err_st)) panic(&err_st);
        printf("COMMAND: %s\n", cmd_buf.cmd);
        for (int i = 0; i < cmd_buf.arg_ct; i++) {
            printf("ARG %d: %s\n", i, cmd_buf.args[i]);
        }
    }
    
    return err_st.code;
}
