#ifndef DISPLAY_H
#define DISPLAY_H

#include "GENERAL.H"

void box(unsigned char color, int x0, int y0, int x1, int y1);

void box(unsigned char color, int x0, int y0, int x1, int y1) {
    int x, y;
    for(x = x0; x <= x1; x++) {
        for(y = y0; y <= y1; y++) {
            BYTE(boot_info->vram)[y * (int)boot_info->scrnx + x] = color;
        }
    }
    return ;
}

#endif  // DISPLAY_H