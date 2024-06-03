#include "./H/memory.h"

// void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
//     if (newSize == 0) {
//         free(pointer);
//         return NULL;
//     }

//     void* result = realloc(pointer, newSize);
//     if (result == NULL) exit(1);
//     return result;
// }

void init_gdt_idt(void) {
	struct SEGMENT_DESCRIPTOR 	*gdt = (struct SEGMENT_DESCRIPTOR *) 0x00270000;
	struct GATE_DESCRIPTOR		*idt = (struct GATE_DESCRIPTOR	  *) 0x0026f800;

	int i;

	// GDT
	for (i = 0; i < 8192; i++) {
		set_segmdesc(gdt + i, 0, 0, 0);
	}
	set_segmdesc(gdt + 1, 0xffffffff, 0x00000000, 0x4092);
	set_segmdesc(gdt + 2, 0x0007ffff, 0x00280000, 0x409a);
	load_gtdr(0xffff, 0x00270000);

	// IDT
	for (i = 0; i < 256; i++) {
		set_gatedesc(idt + i, 0, 0, 0);
	}
	load_idtr(0x7ff, 0x0026f800);

	return ;
}

void set_segmdesc(struct SEGMENT_DESCRIPTOR *segm_d, unsigned int limit, int base, int ar) {
	if (limit > 0xfffff) {
		ar |= 0x8000; /* G_bit = 1 */
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
