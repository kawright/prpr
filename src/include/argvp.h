// Copyright (C) 2024  Kristoffer A. Wright

/*
 * argvp.h - Argument Vector Parsing
 */

#ifndef __ARGVP_H__
#define __ARGVP_H__

#include <stdbool.h>

#include "err.h"

/*
 * String used by getopt to specify options.
 */
#define ARGVP_OPTSTR        "hv"

/*
 * Struct type for storing parsed program options.
 */
typedef struct __PROG_OPTS__ {
    bool        show_help;
    bool        show_ver;
    char        *fname;
} ProgOpts;

/*
 * Initialize a ProgOpts
 */
void init_prog_opts(ProgOpts *prog_opts);

/*
 * Parse the argument vector and write them to a ProgOpts. Throws ERR_ARGV if the argument vector is malformed.
 */
void parse_prog_opts(ProgOpts *prog_opts, int argc, char *argv[], ErrSt *err_st);

#endif
