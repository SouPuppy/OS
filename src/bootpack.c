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

	int a = 12345;
	char name[10] = "XYL";
	char c = 'S';
	_fprintf(stdout, "%s D%cB%d", name, c, a);

	// print_char(white, i += 8, 8, 'Z');
	// print_char(white, i += 8, 8, 'H');

	// print_char(white, i += 8, 8, ' ');
	
	// print_char(white, i += 8, 8, 'D');
	// print_char(white, i += 8, 8, 'S');
	// print_char(white, i += 8, 8, 'B');
	
	
	for (;;) {
		io_hlt();
	}
}
