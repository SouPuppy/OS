#ifndef BOOTINFO_H
#define BOOTINFO_H

#include "common.h"

#define ADR_BOOTINFO	0x00000ff0

typedef struct BOOTINFO{
	uint8_t  cyls, leds, vmode, reserve;
	uint16_t scrnx, scrny;
	uint32_t *vram;
};

extern struct BOOTINFO *boot_info;

void init_bootinfo(void);

#endif  // BOOTINFO_H
