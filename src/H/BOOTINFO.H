#ifndef BOOTINFO_H
#define BOOTINFO_H

#include "GENERAL.H"

typedef struct BOOTINFO{
	uint8_t  cyls, leds, vmode, reserve;
	uint16_t scrnx, scrny;
	uint32_t *vram;
} BOOTINFO;

struct BOOTINFO *boot_info;

void init_bootinfo() {
	// see in asmhead.nas
    boot_info = (struct BOOTINFO *) 0x0ff0;
}

#endif  // BOOTINFO_H