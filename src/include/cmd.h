// Copyright (C) 2024  Kristoffer A. Wright

/*
 * cmd.h - Commands
 */

#ifndef __CMD_H__
#define __CMD_H__

#include "chmat.h"
#include "graphic.h"

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
void cmd_quitgraph(GraphSt *graph_st);

/*
 * Enable/disable command feedback.
 */
void cmd_fdback(bool val);

/*
 * Draw the character matrix to the graphics buffer.
 */
void cmd_pngdraw(GraphSt *graph_st, ChMat *ch_mat, ErrSt *err_st);

/*
 * Save the graphics buffer as a png file.
 */
void cmd_pngsv(GraphSt *graph_st, char *fname, ErrSt *err_st); 

/*
 * Put a left-aligned string onto a ChMat. Throws ERR_RANGE if the string goes out-of-bounds.
 */
void cmd_putl(ChMat *ch_mat, uint16_t x, uint16_t y, char *str);

/*
 * Put a right-aligned string onto a ChMat. Throws ERR_RANGE if the string goes out-of-bounds.
 */
void cmd_putr(ChMat *ch_mat, uint16_t x, uint16_t y, char *str);

#endif
