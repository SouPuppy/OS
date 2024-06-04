#include "./H/common.h"
#include "./H/pic.h"

#include "./H/io.h"

// I don't know what the f* are those and I will never know.
void init_pic(void) {
    io_out8(PIC0_IMR,  0xff  );
    io_out8(PIC1_IMR,  0xff  );

    io_out8(PIC0_ICW1, 0x11  );
    io_out8(PIC0_ICW2, 0x20  );
    io_out8(PIC0_ICW3, 1 << 2);
    io_out8(PIC0_ICW4, 0x01  );

    io_out8(PIC1_ICW1, 0x11  );
    io_out8(PIC1_ICW2, 0x28  );
    io_out8(PIC1_ICW3, 2     );
    io_out8(PIC1_ICW4, 0x01  );

    io_out8(PIC0_IMR,  0xfb  );
    io_out8(PIC1_IMR,  0xff  );
	return ;
}

#define PORT_KEYDAT		0x0060

char keybuf[32];
struct FIFO keyfifo;

void init_keyboard_buf() {
	fifo_init(&keyfifo, 32, keybuf);
}

void fifo_init(struct FIFO *fifo, int size, unsigned char *buf) {
	fifo->size = size;
	fifo->buf = buf;
	fifo->free = size;
	fifo->flag = 0;

	fifo->ptr_w = 0;
	fifo->ptr_r = 0;
}

int fifo_enq(struct FIFO *fifo, unsigned char data) { // enqueue
	if (fifo->free == 0) { // queue overflow~
		fifo->flag |= FLAGS_OVERFLOW;
		return -1;
	}
	fifo->buf[fifo->ptr_w] = data;
	fifo->ptr_w ++;
	if (fifo->ptr_w == fifo->size) {
		fifo->ptr_w = 0;
	}
	fifo->free --;
	return 0;
}

int fifo_deq(struct FIFO *fifo) { // dequeue
	unsigned char data;
	if (fifo->free == fifo->size) {
		// no data
		return -1;
	}
	data = fifo->buf[fifo->ptr_r];
	fifo->ptr_r ++;
	if (fifo->ptr_r == fifo->size) {
		fifo->ptr_r = 0;
	}
	fifo->free ++;
	return data;
}

int fifo_count(struct FIFO *fifo) {
	return fifo->size - fifo->free;
}

void inthandler21(int *esp) { // keyboard
	unsigned char data;
	io_out8(PIC0_OCW2, 0x61);
	data = io_in8(PORT_KEYDAT);
	fifo_enq(&keyfifo, data);
	return ;
}

void inthandler2c(int *esp) { // mouse
	// struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	// boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
	_fprintf(stdout, "INT 2C (IRQ-12) : PS/2 mouse");
	for (;;) {
		io_hlt();
	}
}

void inthandler27(int *esp) {
	io_out8(PIC0_OCW2, 0x67);
	return;
}
