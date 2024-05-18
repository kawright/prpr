// Copyright (C) 2024  Kristoffer A. Wright

/*
 * argvp.c - Argument Vector Parsing
 */

#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>

#include "argvp.h"
#include "err.h"

void init_prog_opts(ProgOpts *prog_opts) {
    prog_opts->show_help        = false;
    prog_opts->show_ver         = false;
    prog_opts->fname            = NULL; 
}

void parse_prog_opts(ProgOpts *prog_opts, int argc, char *argv[], ErrSt *err_st) {
    int curr_opt;
    while ((curr_opt = getopt(argc, argv, ARGVP_OPTSTR)) != -1) {
        switch (curr_opt) {
            case 'h':
            prog_opts->show_help = true;
            break;
            
            case 'v':
            prog_opts->show_ver = true;
            break;

            case '?':
            throw(err_st, ERR_ARGV, "Unknown option -%c", optopt);
            return;

            default:
            return;
        }
    }
    if (optind == argc - 1) {
        prog_opts->fname = argv[optind];
        return;
    }
    if (optind == argc) {
        prog_opts->fname = NULL;
        return;
    }
    throw(err_st, ERR_ARGV, "0 or 1 positional argument expected, but %d given", argc - optind);
}
