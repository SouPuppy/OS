#ifndef BOOTINFO_H
#define BOOTINFO_H

#include "common.h"

typedef struct BOOTINFO{
	uint8_t  cyls, leds, vmode, reserve;
	uint16_t scrnx, scrny;
	uint32_t *vram;
};

void init_bootinfo(void);

#endif  // BOOTINFO_H
