#include "./H/common.h"

#include "./H/bootinfo.h"
#include "./H/palette.h"
#include "./H/dsctbl.h"
#include "./H/pic.h"
#include "./H/terminal.h"
#include "./H/device.h"

#include "./H/io.h"

void initiate(void) {
	init_bootinfo();
	init_gdtidt();
	init_pic();
	io_sti();

	init_keyboard_buf();	// pic.h
	init_mouse_buf();		// pic.h
	io_out8(PIC0_IMR, 0xf9);	// KB 11111001
	io_out8(PIC1_IMR, 0xef);	// MS 11101111
	init_keyboard();	// device.h
	init_mouse();		// device.h
	enable_keyboard();	// pic.h
	enable_mouse();		// pic.h

	init_palette();
	init_io();
	init_main_terminal();

	_fprintf(stdout, "Initiated\n\tHello world!\n");
}

void HariMain(void) {
	int i;
	unsigned char *bf;
	initiate();

	for (;;) {
		io_cli();
		if		(detect_mouse() == 3) {
			bf = mouse_data_buf();
			_fprintf(stdout, "detect mouse     %d\t%d\t%d\n", bf[0], bf[1], bf[2]);			
		}
		else if (detect_keyboard() == 1) {
			bf = keyboard_data();
			_fprintf(stdout, "detect keyborard %d\n", bf[0]);
		}
		else {
			io_stihlt();
		}
	}
}
