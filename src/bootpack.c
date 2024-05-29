#include "./H/GENERAL.H"
#include "./H/BOOTINFO.H"
#include "./H/PALETTE.H"

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

void initiate(void) {
	init_bootinfo();
	init_palette();
}

void HariMain(void)
{
	initiate();
	// vram = (char *) 0xa0000;
	// xsize = 320;
	// ysize = 200;

	boxfill8(vram, xsize, iris,  0,         0,          xsize -  1, ysize - 29);
	boxfill8(vram, xsize, white,  0,         ysize - 28, xsize -  1, ysize - 28);
	boxfill8(vram, xsize, 2,  0,         ysize - 27, xsize -  1, ysize - 27);
	boxfill8(vram, xsize, white,  0,         ysize - 26, xsize -  1, ysize -  1);

	boxfill8(vram, xsize, 2,  3,         ysize - 24, 59,         ysize - 24);
	boxfill8(vram, xsize, 2,  2,         ysize - 24,  2,         ysize -  4);
	boxfill8(vram, xsize, 3,  3,         ysize -  4, 59,         ysize -  4);
	boxfill8(vram, xsize, 3, 59,         ysize - 23, 59,         ysize -  5);
	boxfill8(vram, xsize, 4,  2,         ysize -  3, 59,         ysize -  3);
	boxfill8(vram, xsize, 4, 60,         ysize - 24, 60,         ysize -  3);

	boxfill8(vram, xsize, 3, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill8(vram, xsize, 3, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill8(vram, xsize, 2, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill8(vram, xsize, 2, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

	for (;;) {
		io_hlt();
	}
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y;
	for (y = y0; y <= y1; y++) {
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}