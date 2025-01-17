#ifndef DSCTBL_H
#define DSCTBL_H

#include "common.h"

#define ADR_IDT			0x0026f800
#define LIMIT_IDT		0x000007ff
#define ADR_GDT			0x00270000
#define LIMIT_GDT		0x0000ffff
#define ADR_BOTPAK		0x00280000
#define LIMIT_BOTPAK	0x0007ffff
#define AR_DATA32_RW	0x4092
#define AR_CODE32_ER	0x409a
#define AR_INTGATE32	0x008e

typedef struct SEGMENT_DESCRIPTOR {
	short 	limit_low	, base_low;
	char 	base_mid	, access_right;
	char 	limit_high	, base_high;
} __attribute__((packed)) SEGMENT_DESCRIPTOR;

typedef struct GATE_DESCRIPTOR {
	short 	offset_low	, selector;
	char 	dw_count	, access_right;
	short 	offset_high;
} __attribute__((packed)) GATE_DESCRIPTOR;

void init_gdtidt(void);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *segm_d, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gate_d, int offset, int selector, int ar);


#endif  // DSCTBL_H
