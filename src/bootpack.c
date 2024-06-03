#include "./H/common.h"
#include "./H/bootinfo.h"
#include "./H/palette.h"
#include "./H/memory.h"
#include "./H/display.h"
#include "./H/io.h"

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern struct BOOTINFO *boot_info;

void initiate(void) {
	init_bootinfo();
	init_palette();
	init_gdt_idt();
	init_io();
}

void HariMain(void) {
	initiate();
	box(black, 0, 0, boot_info->scrnx, boot_info->scrny);
	_fprintf(stdout, "asdasdasdasd");
	for (;;) {
		io_hlt();
	}
}
