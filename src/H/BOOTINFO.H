#ifndef BOOTINFO_H
#define BOOTINFO_H

#include "GENERAL.H"

typedef struct BOOTINFO{
	uint8_t  cyls, leds, vmode, reserve;
	uint16_t scrnx, scrny;
	uint32_t *vram;
};

#endif  // BOOTINFO_H
