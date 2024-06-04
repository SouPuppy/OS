#include "./H/common.h"

#include "./H/bootinfo.h"
#include "./H/palette.h"
#include "./H/dsctbl.h"
#include "./H/pic.h"
#include "./H/terminal.h"


#include "./H/io.h"

void initiate(void) {
	init_keyboard_buf();
	init_bootinfo();  	// #1

	// 
	init_gdtidt();
	init_pic();
	io_sti();			// set interrupt flag

	io_out8(PIC0_IMR, 0xf9);	// KB 11111001
	
	io_out8(PIC1_IMR, 0xef);	// MS 11101111
	

	// graphs
	init_palette();
	init_io();			// # -2
	init_main_terminal();	// # -1
	_fprintf(stdout, "Initiated\n\tHello world!\n");
}

void HariMain(void) {
	int i;
	initiate();
	io_hlt();
	for (;;) {
		io_cli();
		if (fifo_count(&keyfifo) == 0) {
			io_stihlt();
		} else {
			i = fifo_deq(&keyfifo);
			io_sti();

			_fprintf(stdout, "detect: %d, \t[%d/32] remaining\n", i, fifo_count(&keyfifo));
			// _fprintf(stdout, "%c", '0' + fifo_count(&keyfifo));
		}
	}
}
