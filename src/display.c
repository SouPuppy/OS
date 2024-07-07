#include "./H/common.h"
#include "./H/bootinfo.h"
#include "./H/display.h"

extern struct BOOTINFO *boot_info;
extern char EZ_font[4096];

void box(char *vram, unsigned char color, int frame_width, int x0, int y0, int xsize, int ysize) {
    int x, y, ix, iy;
    for(iy = 0, y = y0; iy < ysize; iy++, y++) {
        for(ix = 0, x = x0; ix < xsize; ix++, x++) {
            vram[y * frame_width + x] = color;
        }
    }
    return ;
}


void print_char(char *vram, unsigned char color, int fram_width, int x, int y, char c) {
    int i;
    char *p, d;

    for (i = 0; i < 16; i++) {
        p = (char *)vram + ((y + i) * (int)fram_width) + x;
        d = EZ_font[c * 16 + i];
        if ((d & 0x80) != 0) p[0] = color;
        if ((d & 0x40) != 0) p[1] = color;
        if ((d & 0x20) != 0) p[2] = color;
        if ((d & 0x10) != 0) p[3] = color;
        if ((d & 0x08) != 0) p[4] = color;
        if ((d & 0x04) != 0) p[5] = color;
        if ((d & 0x02) != 0) p[6] = color;
        if ((d & 0x01) != 0) p[7] = color;
    }
}

void block_of_color(char *vram, int vxsize, int vysize, int block_x, int block_y, int x0, int y0, char *buff) {
    int ix, iy, bx, by;
    for (by = 0, iy = y0; by < block_y; by++, iy++) {
        for (bx = 0, ix = x0; bx < block_x; bx++, ix++) {
            vram[iy *vxsize + ix] 
                = buff[by * block_x + bx];
        }    
    }
    return ;
}
