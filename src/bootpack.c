#include "./H/common.h"

#include "./H/bootinfo.h"
#include "./H/palette.h"
#include "./H/dsctbl.h"
#include "./H/pic.h"
#include "./H/terminal.h"
#include "./H/device.h"

#include "./H/io.h"
#include "./H/memory.h"
#include "H/display.h"
#include "H/windows.h"


void initiate(void) {
	init_bootinfo();

	init_gdtidt();
	init_pic();
	io_sti();
	init_memman();				// memory.h

	init_palette();
	init_io();

	init_windows();				// windows.h
	init_main_terminal();


	init_keyboard_buf();		// pic.h
	init_mouse_buf();			// pic.h
	io_out8(PIC0_IMR, 0xf9);	// KeyBoard 11111001
	io_out8(PIC1_IMR, 0xef);	// Mouse	11101111
	init_keyboard_detect();		// device.h
	init_mouse_detect();		// device.h
	enable_keyboard();			// pic.h
	enable_mouse();				// pic.h

	init_mouse();
	
	_fprintf(stdout, "Initiated\n\tHello world!\n");
}

void HariMain(void) {
	initiate();
	windows_refresh(WINDOWS);
	mem_debug();
	for (;;) {
		{
			// display_crusor();
		}

		io_cli();
		if (detect_mouse(ms_det) == 3) {
			_fprintf(stdout, "MOUSE [%d\t%d]\t%c\n", ms_det->x, ms_det->y, "_LR C"[ms_det->btn]);
			
			update_crusor_position(ms_det->x, ms_det->y);
		}
		else if (detect_keyboard(kb_det) == 1) {
			
			_fprintf(stdout, "KEYBOARD %d\n", kb_det->data);
		}
		else {
			io_stihlt();
		}
	}
}

