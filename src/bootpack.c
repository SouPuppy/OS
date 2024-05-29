#include "./H/GENERAL.H"
#include "./H/BOOTINFO.H"
#include "./H/PALETTE.H"
#include "./H/DISPLAY.H"

void initiate(void) {
	init_bootinfo();
	init_palette();
}

void HariMain(void) {
	initiate();
	
	box(white, 11, 1, 120, 120);

	for (;;) {
		io_hlt();
	}
}
