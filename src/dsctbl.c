#include "./H/common.h"
#include "./H/dsctbl.h"
#include "./H/pic.h"

void init_gdtidt(void)
{
	struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *) ADR_GDT;
	struct GATE_DESCRIPTOR    *idt = (struct GATE_DESCRIPTOR    *) ADR_IDT;
	int i;

	// init GDT
	for (i = 0; i <= LIMIT_GDT / 8; i++) {
		set_segmdesc(gdt + i, 0, 0, 0);
	}
	set_segmdesc(gdt + 1, 0xffffffff,   0x00000000, AR_DATA32_RW);
	set_segmdesc(gdt + 2, LIMIT_BOTPAK, ADR_BOTPAK, AR_CODE32_ER);
	load_gdtr(LIMIT_GDT, ADR_GDT);	// load gdt reserve

	// init IDT
	for (i = 0; i <= LIMIT_IDT / 8; i++) {
		set_gatedesc(idt + i, 0, 0, 0);
	}
	load_idtr(LIMIT_IDT, ADR_IDT);	// // load idt reserve

	// IDT setting
	set_gatedesc(idt + 0x21, (int) asm_inthandler21, 2 * 8, AR_INTGATE32);
	set_gatedesc(idt + 0x27, (int) asm_inthandler27, 2 * 8, AR_INTGATE32);
	set_gatedesc(idt + 0x2c, (int) asm_inthandler2c, 2 * 8, AR_INTGATE32);

	return;
}

void set_segmdesc(struct SEGMENT_DESCRIPTOR *segm_d, unsigned int limit, int base, int ar) {
	if (limit > 0xfffff) {
		ar |= 0x8000;
		limit /= 0x1000;
	}
	segm_d->limit_low    = limit & 0xffff;
	segm_d->base_low     = base & 0xffff;
	segm_d->base_mid     = (base >> 16) & 0xff;
	segm_d->access_right = ar & 0xff;
	segm_d->limit_high   = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
	segm_d->base_high    = (base >> 24) & 0xff;
	return;
}

void set_gatedesc(struct GATE_DESCRIPTOR *gate_d, int offset, int selector, int ar) {
	gate_d->offset_low   = offset & 0xffff;
	gate_d->selector     = selector;
	gate_d->dw_count     = (ar >> 8) & 0xff;
	gate_d->access_right = ar & 0xff;
	gate_d->offset_high  = (offset >> 16) & 0xffff;
	return;
}
