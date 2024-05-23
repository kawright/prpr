// Copyright (C) 2024  Kristoffer A. Wright

/*
 * main.c - Entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "asset.h"
#include "chmat.h"
#include "cmd.h"
#include "cmdbuf.h"
#include "err.h"
#include "lnbuf.h"
#include "graphic.h"
#include "fdback.h"
#include "argvp.h"

int main(int argc, char *argv[]) {
    ErrSt       err_st;
    LnBuf       ln_buf;
    CmdBuf      cmd_buf;
    ChMat       ch_mat;
    GraphSt     graph_st;
    ProgOpts    prog_opts;
    init_err_st(&err_st);
    init_ln_buf(ln_buf);
    init_cmd_buf(&cmd_buf);
    init_ch_mat(&ch_mat);
    init_graph_st(&graph_st);
    init_prog_opts(&prog_opts);
    init_assets();

    parse_prog_opts(&prog_opts, argc, argv, &err_st);
    if (is_err_thrown(&err_st)) panic(&err_st);
    
    if (prog_opts.show_ver) {
        printf("%s\n", _binary_asset_version_txt_start);
        return 0;
    }
    if (prog_opts.show_help) {
        printf("%s\n", _binary_asset_help_txt_start);
        return 0;
    }
    
    ///// INPUT LOOP /////

    FILE *fp;
    bool batch_mode         = false;
    if (prog_opts.fname) {
        batch_mode = true;
        fp = fopen(prog_opts.fname, "r");
        if (fp == NULL) {
            throw(&err_st, ERR_ARGV, "Could not open file %s", prog_opts.fname);
            panic(&err_st);
        }
    }
    while (true) {
        
        if (batch_mode) {
            if (!(fgets(ln_buf, MAX_LN_LEN, fp))) {
                batch_mode = false;
                fclose(fp);
                printf(">>> ");
                fgets(ln_buf, MAX_LN_LEN, stdin);
            };
        } else {
            printf(">>> ");
            fgets(ln_buf, MAX_LN_LEN, stdin);
        }
        
        init_cmd_buf(&cmd_buf);
        parse_cmd(&cmd_buf, ln_buf, &err_st);
        if (is_err_thrown(&err_st)) panic(&err_st);
    
        // quit
        if (strcmp(cmd_buf.cmd, "quit") == 0) {
            if (cmd_buf.arg_ct != 0) {
                fdback_err();
                continue;
            }
            cmd_quit();

        // dim cols rows
        } else if (strcmp(cmd_buf.cmd, "dim") == 0) {
            if (cmd_buf.arg_ct != 2) {
                fdback_err();
                continue;
            }
            cmd_dim(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), &err_st);
            if (is_err_thrown(&err_st)) panic(&err_st);
        
        // fill ch
        } else if (strcmp(cmd_buf.cmd, "fill") == 0) {
            if ((cmd_buf.arg_ct != 1) || (strlen(cmd_buf.args[0]) != 1)) {
                fdback_err();
                continue; 
            }
            cmd_fill(&ch_mat, cmd_buf.args[0][0]);

        // print   
        } else if (strcmp(cmd_buf.cmd, "print") == 0) {
            if (cmd_buf.arg_ct != 0) {
                fdback_err();
                continue;
            }
            cmd_print(&ch_mat);

        // txt fname
        } else if (strcmp(cmd_buf.cmd, "txt") == 0) {
            if (cmd_buf.arg_ct != 1) {
                fdback_err();
                continue;
            }
            cmd_txt(&ch_mat, cmd_buf.args[0]);

        // initgraph
        } else if (strcmp(cmd_buf.cmd, "initgraph") == 0) {
            if (cmd_buf.arg_ct != 0) {
                fdback_err();
                continue;
            }
            INIT_GRAPHICS();
            if (is_err_thrown(&err_st)) {
                fdback_err();
                init_err_st(&err_st);
                continue;
            }
            ld_fnt(&graph_st, FNT_ATI, 12, &err_st);
            if (is_err_thrown(&err_st)) {
                fdback_err();
                init_err_st(&err_st);
                continue;
            }
            fdback_ok(); 

        // quitgraph
        } else if (strcmp(cmd_buf.cmd, "quitgraph") == 0) {
            if (cmd_buf.arg_ct != 0) {
                fdback_err();
                continue;
            }
            cmd_quitgraph(&graph_st); 
    
        // fdback [on|off]
        } else if (strcmp(cmd_buf.cmd, "fdback") == 0) {
            if (cmd_buf.arg_ct != 1) {
                fdback_err();
                continue;
            }
            if (strcmp(cmd_buf.args[0], "on") == 0) {
                cmd_fdback(true);
            } else if (strcmp(cmd_buf.args[0], "off") == 0) {
                cmd_fdback(false);
            } else {
                fdback_err();
            }

        // pngdraw
        } else if (strcmp(cmd_buf.cmd, "pngdraw") == 0) {
            if (cmd_buf.arg_ct != 0) {
                fdback_err();
                continue;
            }
            cmd_pngdraw(&graph_st, &ch_mat, &err_st);
            if (is_err_thrown(&err_st)) {
                fdback_err();
                continue;
            }

        // pngsv fname
        } else if (strcmp(cmd_buf.cmd, "pngsv") == 0) {
            if (cmd_buf.arg_ct != 1) {
                fdback_err();
                continue;
            }
            cmd_pngsv(&graph_st, cmd_buf.args[0], &err_st);
            if (is_err_thrown(&err_st)) {
                fdback_err();
                continue;
            }

        // putl x y str
        } else if (strcmp(cmd_buf.cmd, "putl") == 0) {
            if (cmd_buf.arg_ct != 3) {
                fdback_err();
                continue;
            }
            cmd_putl(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), cmd_buf.args[2]);

        // putr x y str
        } else if (strcmp(cmd_buf.cmd, "putr") == 0) {
            if (cmd_buf.arg_ct != 3) {
                fdback_err();
                continue;
            }
            cmd_putr(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), cmd_buf.args[2]);

        // putc ln str
        } else if (strcmp(cmd_buf.cmd, "putc") == 0) {
            if (cmd_buf.arg_ct != 2) {
                fdback_err();
                continue;
            }
            cmd_putc(&ch_mat, atoi(cmd_buf.args[0]), cmd_buf.args[1]);
   
        // hrule ln ch 
        } else if (strcmp(cmd_buf.cmd, "hrule") == 0) {
            if (cmd_buf.arg_ct != 2) {
                fdback_err();
                continue;
            }
            if (strlen(cmd_buf.args[1]) != 1) {
                fdback_err();
                continue;
            }
            cmd_hrule(&ch_mat, atoi(cmd_buf.args[0]), cmd_buf.args[1]);
   
        // fbox uplx uply botrx botry ch
        } else if (strcmp(cmd_buf.cmd, "fbox") == 0) {
            if (cmd_buf.arg_ct != 5) {
                fdback_err();
                continue;
            }
            if (strlen(cmd_buf.args[4]) != 1) {
                fdback_err();
                continue;
            }
            cmd_fbox(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), atoi(cmd_buf.args[2]), 
                atoi(cmd_buf.args[3]), cmd_buf.args[4]);

        // box uplx uply botrx botry horiz [vert] [crnr]
        } else if (strcmp(cmd_buf.cmd, "box") == 0) {
            if (cmd_buf.arg_ct == 5) {
                if (strlen(cmd_buf.args[4]) != 1) {
                    fdback_err();
                    continue;
                }
                cmd_box(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), atoi(cmd_buf.args[2]),
                    atoi(cmd_buf.args[3]), cmd_buf.args[4], cmd_buf.args[4], cmd_buf.args[4]);
            } else if (cmd_buf.arg_ct == 7) {
                if (
                        (strlen(cmd_buf.args[4]) != 1) ||
                        (strlen(cmd_buf.args[5]) != 1) ||
                        (strlen(cmd_buf.args[6]) != 1)) {
                    fdback_err();
                    continue;
                }
                cmd_box(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), atoi(cmd_buf.args[2]),
                    atoi(cmd_buf.args[3]), cmd_buf.args[4], cmd_buf.args[5], cmd_buf.args[6]);
            } else {
                fdback_err();
                continue;
            }

        // fnt name pt
        } else if (strcmp(cmd_buf.cmd, "fnt") == 0) {
            if (cmd_buf.arg_ct != 2) {
                fdback_err();
                continue;
            }
            cmd_fnt(&graph_st, cmd_buf.args[0], atoi(cmd_buf.args[1]), &err_st);

        // fg r g b
        } else if (strcmp(cmd_buf.cmd, "fg") == 0) {
            if (cmd_buf.arg_ct != 3) {
                fdback_err();
                continue;
            }
            cmd_fg(&graph_st, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), atoi(cmd_buf.args[2]));
        
        // bg r g b
        } else if (strcmp(cmd_buf.cmd, "bg") == 0) {
            if (cmd_buf.arg_ct != 3) {
                fdback_err();
                continue;
            }
            cmd_bg(&graph_st, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), atoi(cmd_buf.args[2]));

        // cp x y fname start lns
        } else if (strcmp(cmd_buf.cmd, "cp") == 0) {
            if (cmd_buf.arg_ct != 5) {
                fdback_err();
                continue;
            }
            cmd_cp(&ch_mat, atoi(cmd_buf.args[0]), atoi(cmd_buf.args[1]), cmd_buf.args[2], atoi(cmd_buf.args[3]),
                atoi(cmd_buf.args[4]));

        // lnsp px
        } else if (strcmp(cmd_buf.cmd, "lnsp") == 0) {
            if (cmd_buf.arg_ct != 1) {
                fdback_err();
                continue;
            }
            cmd_lnsp(&graph_st, atoi(cmd_buf.args[0]));

        // echo cmd
        } else if (strcmp(cmd_buf.cmd, "echo") == 0) {
            if (cmd_buf.arg_ct != 1) {
                fdback_err();
                continue;
            }
            cmd_echo(cmd_buf.args[0]);

        // -- [comment]
        } else if (strcmp(cmd_buf.cmd, "--") == 0) {
            continue;

        // Blank line
        } else if (strcmp(cmd_buf.cmd, "") == 0) {
            continue;

        // Unknown Command
        } else {
            fdback_err();
        }
    }
    
    return err_st.code;
}
            
