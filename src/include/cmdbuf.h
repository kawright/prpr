// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmdbuf.h - Command buffer
 */

#ifndef __CMDBUF_H__
#define __CMDBUF_H__

#include <stdint.h>

#include "err.h"
#include "lnbuf.h"


/*
 * The size of the character array allocated for individual arguments.
 */
#define MAX_CMD_ARG_LEN     511


/*
 * The maximum number of arguments that can be parsed.
 */
#define MAX_CMD_ARG_CT      64


/*
 * Type alias for a character array used for individual arguments.
 */
typedef char CmdArg[MAX_CMD_ARG_LEN + 1];


/*
 * Struct type for storing a single command and its arguments.
 */
typedef struct __CMD_BUF__ {
    CmdArg      cmd;
    CmdArg      args[MAX_CMD_ARG_CT];
    uint8_t     arg_ct;
} CmdBuf;


/*
 * Initialize a CmdBuf.
 */
void init_cmd_buf(CmdBuf *cmd_buf);


/*
 * Parse a LnBuf and write the parsed values to a CmdBuf. Throws ERR_SYNTAX if the LnBuf is malformed.
 */
void parse_cmd(CmdBuf *cmd_buf, const LnBuf *ln_buf, ErrSt *err_st);

#endif
