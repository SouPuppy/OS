#include "./H/common.h"
#include "./H/pic.h"

#include "./H/display.h"

// #include "./H/io.h"
// extern FILE *stdin;
// extern FILE *stdout;
// extern FILE *stderr;

// I don't know what the f* are those and I will never know.
void init_pic(void) {
    io_out_BYTE(PIC0_IMR, 0xff);
    io_out_BYTE(PIC1_IMR, 0xff);

    io_out_BYTE(PIC0_ICW1, 0x11);
    io_out_BYTE(PIC0_ICW2, 0x20);
    io_out_BYTE(PIC0_ICW3, 1 << 2);
    io_out_BYTE(PIC0_ICW4, 0x01);

    io_out_BYTE(PIC1_ICW1, 0x11);
    io_out_BYTE(PIC1_ICW2, 0x28);
    io_out_BYTE(PIC1_ICW3, 2);
    io_out_BYTE(PIC1_ICW4, 0x01);

    io_out_BYTE(PIC0_IMR, 0xfb);
    io_out_BYTE(PIC1_IMR, 0xff);
}

void inthandler21(int *esp) { // keyboard
	// struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	// boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
	// _fpriintf(stdout, "INT 21 (IRQ-1) : PS/2 keyboard");
	for (;;) {
		io_hlt();
	}
}

void inthandler2c(int *esp) { // mouse
	// struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	// boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
	// _fpriintf(stdout, "INT 2C (IRQ-12) : PS/2 mouse");
	for (;;) {
		io_hlt();
	}
}

void inthandler27(int *esp) {
	io_out_BYTE(PIC0_OCW2, 0x67); /* 通知PIC的IRQ-07（参考7-1） */
	return;
}
