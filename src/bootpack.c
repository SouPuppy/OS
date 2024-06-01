#include "./H/GENERAL.H"
#include "./H/BOOTINFO.H"
#include "./H/PALETTE.H"
#include "./H/DISPLAY.H"

extern struct BOOTINFO *boot_info;

void initiate(void) {
	init_bootinfo();
	init_palette();
}



void HariMain(void) {
	initiate();
	
	box(black, 0, 0, boot_info->scrnx, boot_info->scrny);
	
	int i = 0;
	print_char(white, i += 8, 8, foo('A'));
	print_char(white, i += 8, 8, 'H');
	print_char(white, i += 8, 8, 'N');

	print_char(white, i += 8, 8, ' ');
	
	print_char(white, i += 8, 8, 'D');
	print_char(white, i += 8, 8, 'S');
	print_char(white, i += 8, 8, 'B');
	
	
	for (;;) {
		io_hlt();
	}
}
