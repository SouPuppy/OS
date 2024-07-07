#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"
#include "io.h"

// ----- 16x colors -----

#define true_red        0
#define scarlet         1
#define rose            2
#define tangerine       3
#define amber           4
#define willow          5
#define green           6
#define aquamarine      7
#define dark_teal       8
#define azure           9
#define dark_blue       10
#define iris            11
#define white           12
#define skin            13
#define withered_tea    14
#define black           15

void box(char *vram, unsigned char color, int frame_width, int x0, int y0, int xsize, int ysize);
void print_char(char *vram, unsigned char color, int fram_width, int x, int y, char c);
void block_of_color(char *vram, int vxsize, int vysize, int block_x, int block_y, int x0, int y0, char *buff);

#endif  // DISPLAY_H
