#include "./H/common.h"
#include "./H/bootinfo.h"
#include "./H/display.h"

extern struct BOOTINFO *boot_info;
extern char EZ_font[4096];

void box(char *vram, unsigned char color, int frame_width, int x0, int y0, int x1, int y1) {
    int x, y;
    for(x = x0; x <= x1; x++) {
        for(y = y0; y <= y1; y++) {
            BYTE(vram)[y * frame_width + x] = color;
        }
    }
    return ;
}

void print_char(unsigned char color, int x, int y, char c) {
    int i;
    char *p, d;

    for (i = 0; i < 16; i++) {
        p = (char *)boot_info->vram + ((y + i) * (int)boot_info->scrnx) + x;
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
