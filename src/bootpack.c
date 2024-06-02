#include "./H/common.h"
#include "./H/bootinfo.h"
#include "./H/palette.h"
#include "./H/display.h"
#include "./H/io.h"

// extern struct BOOTINFO *boot_info;
extern struct BOOTINFO *boot_info;

void init_bootinfo() {
	// see in asmhead.nas
    boot_info = (struct BOOTINFO *) 0x0ff0;
}

void initiate(void) {
	init_bootinfo();
	init_palette();

	init_IO();
}

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

void HariMain(void) {
	initiate();
	
	box(black, 0, 0, boot_info->scrnx, boot_info->scrny);
	_fprintf(stdout, "asdasdasd");

	


	for (;;) {
		io_hlt();
	}
}
