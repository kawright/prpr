// Copyright (C) 2024  Kristoffer A. Wright

/*
 * main.c - Entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chmat.h"
#include "cmd.h"
#include "cmdbuf.h"
#include "err.h"
#include "lnbuf.h"

int main(int argc, char *argv[]) {
    ErrSt   err_st;
    LnBuf   ln_buf;
    CmdBuf  cmd_buf;
    ChMat   ch_mat;
    init_err_st(&err_st);
    init_ln_buf(ln_buf);
    init_cmd_buf(&cmd_buf);
    init_ch_mat(&ch_mat);

    ///// INPUT LOOP /////

    while (true) {
        printf(">>> ");
        fgets(ln_buf, MAX_LN_LEN, stdin);
        
        init_cmd_buf(&cmd_buf);
        parse_cmd(&cmd_buf, ln_buf, &err_st);
        if (is_err_thrown(&err_st)) panic(&err_st);
    
        // quit
        if (strcmp(cmd_buf.cmd, "quit") == 0) {
            if (cmd_buf.arg_ct != 0) {
                printf("ERR\n");
                continue;
            }
            cmd_quit();

        // dim cols rows
        } else if (strcmp(cmd_buf.cmd, "dim") == 0) {
            if (cmd_buf.arg_ct != 2) {
                printf("ERR\n");
                continue;
            }
            cmd_dim(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), &err_st);
            if (is_err_thrown(&err_st)) panic(&err_st);
        
        // fill ch
        } else if (strcmp(cmd_buf.cmd, "fill") == 0) {
            if ((cmd_buf.arg_ct != 1) || (strlen(cmd_buf.args[0]) != 1)) {
                printf("ERR\n");
                continue; 
            }
            cmd_fill(&ch_mat, cmd_buf.args[0][0]);

        // print   
        } else if (strcmp(cmd_buf.cmd, "print") == 0) {
            if (cmd_buf.arg_ct != 0) {
                printf("ERR\n");
                continue;
            }
            cmd_print(&ch_mat);

        // txt fname
        } else if (strcmp(cmd_buf.cmd, "txt") == 0) {
            if (cmd_buf.arg_ct != 1) {
                printf("ERR\n");
                continue;
            }
            cmd_txt(&ch_mat, cmd_buf.args[0]);
        
        // Unknown Command
        } else {
            printf("ERR\n");
        }
    }
    
    return err_st.code;
}
