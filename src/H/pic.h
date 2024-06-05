#ifndef PIC_H
#define PIC_H

#include "common.h"

#define PIC0_ICW1		0x0020
#define PIC0_OCW2		0x0020
#define PIC0_IMR		0x0021
#define PIC0_ICW2		0x0021
#define PIC0_ICW3		0x0021
#define PIC0_ICW4		0x0021
#define PIC1_ICW1		0x00a0
#define PIC1_OCW2		0x00a0
#define PIC1_IMR		0x00a1
#define PIC1_ICW2		0x00a1
#define PIC1_ICW3		0x00a1
#define PIC1_ICW4		0x00a1

void init_pic(void);

void inthandler21(int *esp);
void inthandler27(int *esp);
void inthandler2c(int *esp);



#define FLAGS_OVERFLOW	0x0001

typedef struct FIFO {
	unsigned char *buf;
	int ptr_r, ptr_w, size, free, flag;
};

extern struct FIFO keyfifo;
extern struct FIFO mousefifo;

void init_keyboard_buf(void);
void init_mouse_buf(void);

void fifo_init(struct FIFO *fifo, int size, unsigned char *buf);
int fifo_enq(struct FIFO *fifo, unsigned char data);
int fifo_deq(struct FIFO *fifo);
int fifo_count(struct FIFO *fifo);

#define PORT_KEYDAT				0x0060
#define PORT_KEYSTA				0x0064
#define PORT_KEYCMD				0x0064
#define KEYSTA_SEND_NOTREADY	0x02
#define KEYCMD_WRITE_MODE		0x60
#define KBC_MODE				0x47

void wait_KBC_sendready(void);
void enable_keyboard(void);

#define KEYCMD_SENDTO_MOUSE		0xd4
#define MOUSECMD_ENABLE			0xf4

void enable_mouse(void);

#endif  // PIC_H
