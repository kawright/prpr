// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmdbuf.c - Command buffer
 */

#include "cmdbuf.h"

static void _init_cmd_arg(CmdArg cmd_arg) {
    for (int i = 0; i < MAX_CMD_ARG_LEN; i++) {
        cmd_arg[i] = 0;
    } 
}

void init_cmd_buf(CmdBuf *cmd_buf) {
    _init_cmd_arg(cmd_buf->cmd);
    for (int i = 0; i < MAX_CMD_ARG_CT; i++) {
        _init_cmd_arg(cmd_buf->args[i]);
    }
    cmd_buf->arg_ct = 0;
}

void parse_cmd(CmdBuf *cmd_buf, const LnBuf *ln_buf, ErrSt *err_st) {
    // TODO Finish implementing parse_cmd in cmdbuf.c
    return;
}
