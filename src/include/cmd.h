// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmd.h - Commands
 */

#ifndef __CMD_H__
#define __CMD_H__

#include "chmat.h"

/*
 * Exit the program.
 */
void cmd_quit();

/*
 * Set the output dimensions. Fails if `cols` or `rows` are out of range.
 */
void cmd_dim(ChMat *ch_mat, uint16_t cols, uint16_t rows, ErrSt *err_st);

/*
 * Fill the entire usuable space of a ChMat with a single character.
 */
void cmd_fill(ChMat *ch_mat, char fill_ch);

/*
 * Print the character matrix to the screen.
 */
void cmd_print(ChMat *ch_mat);

/*
 * Dump the character matrix to a text file.
 */
void cmd_txt(ChMat *ch_mat, char *fname);

/*
 * Quit the graphics sub-system.
 */
void cmd_quitgraph();

#endif
