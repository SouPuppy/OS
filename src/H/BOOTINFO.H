#ifndef BOOTINFO_H
#define BOOTINFO_H

#include "GENERAL.H"

char    *vram;
int      xsize, ysize;

short   *boot_info_scrnx, *boot_info_scrny;
int     *boot_info_vram;

void init_bootinfo(void) {

    // aligned with asmhead.lst
    boot_info_scrnx = (short *) 0x0ff4;
    boot_info_scrny = (short *) 0x0ff6;
    boot_info_vram  = (int *)   0x0ff8;

    xsize = *boot_info_scrnx;
	ysize = *boot_info_scrny;
	vram  = (char *) *boot_info_vram;
}

#endif  // BOOTINFO_H