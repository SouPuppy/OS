#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"
#include "io.h"

void dot(unsigned char color, int x, int y);
void box(unsigned char color, int x0, int y0, int x1, int y1);
void print_char(unsigned char color, int x, int y, char c);

#endif  // DISPLAY_H
