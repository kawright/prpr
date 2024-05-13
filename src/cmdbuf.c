// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmdbuf.c - Command buffer
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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

void parse_cmd(CmdBuf *cmd_buf, const LnBuf ln_buf, ErrSt *err_st) {
    int8_t      arg_curs    = -1;
    uint16_t    char_curs   = 0;
    bool        capturing   = false;
    char        stop        = ' ';
    for (int i = 0; i < strlen(ln_buf); i++) {
        if (ln_buf[i] == '\n') {
            if (capturing) arg_curs++;
            break;
        }
        if (capturing) {
            if (ln_buf[i] == stop) {
                capturing = false;
                char_curs = 0;
                arg_curs++;
                if (arg_curs >= MAX_CMD_ARG_CT) {
                    throw(err_st, ERR_SYNTAX, "Too many arguments");
                }
                continue;
            }
            if (arg_curs == -1) {
                cmd_buf->cmd[char_curs] = ln_buf[i];
            } else {
                cmd_buf->args[arg_curs][char_curs] = ln_buf[i];
            }
            char_curs++;
        } else {
            if (ln_buf[i] == ' ') continue;
            if (ln_buf[i] == '"') {
                capturing = true;
                stop = '"';
                continue;
            }
            capturing = true;
            stop = ' ';
            i--;
            continue;
        } 
    }
    if (arg_curs < 0) arg_curs = 0;
    cmd_buf->arg_ct = arg_curs;
    return;
}
