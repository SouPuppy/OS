#include "./H/GENERAL.H"
#include "./H/BOOTINFO.H"
#include "./H/PALETTE.H"
#include "./H/DISPLAY.H"
#include "./H/IO.H"

#define NULL ((void*)0)

FILE *stdin;
FILE *stdout;
FILE *stderr;

FILE _stdin  = (FILE){ 0, NULL, 0, 0 };
FILE _stdout = (FILE){ 1, NULL, 0, 0 };
FILE _stderr = (FILE){ 2, NULL, 0, 0 };

void init_IO() {
    stdin  = &_stdin;
    stdout = &_stdout;
    stderr = &_stderr;
}

int _write(FILE *stream, char c) {
    // boot_info->scrnx;
    if (stream->_file == 1) { // stdout
        static int x = 8, y = 8;
        print_char(white, x, y, c);
        x += 8;
        // if (x >= boot_info->scrnx) {
        //     x = 0;
        //     y += 16;
        // }
        return 1;
    }
    return -1;
}

// extern struct BOOTINFO *boot_info;
struct BOOTINFO *boot_info;
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

	_write(stdout, foo());
	_write(stdout, 'A');
	_write(stdout, 'A');
	_write(stdout, 'A');
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
