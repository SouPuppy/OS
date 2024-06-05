#include "./H/common.h"
#include "./H/device.h"
#include "./H/pic.h"

struct MOUSE    mouse;
struct KEYBOARD keyboard;

void init_mouse() {
    mouse.phase = 0;
}

int detect_mouse() {
    if (fifo_count(&mousefifo) == 0) return -1;
    int data = fifo_deq(&mousefifo);
    io_sti();
    switch (mouse.phase) {
		case 0 :
			if (data == 0xfa) {
				mouse.phase = 1;
			}
			break;
		case 1 :
			mouse.buf[0] = data;
			mouse.phase = 2;
			break;
		case 2 :
			mouse.buf[1] = data;
			mouse.phase = 3;
			break;
		case 3 :
			mouse.buf[2] = data;
			mouse.phase = 1;
			break;
	}
    return mouse.phase;
}

unsigned char* mouse_data_buf() {
    return mouse.buf;
}

void init_keyboard() {
    
}

int detect_keyboard() {
    if (fifo_count(&keyfifo) == 0) return -1;
    int data = fifo_deq(&keyfifo);
    io_sti();
    keyboard.data = data;
    return 1;
}

unsigned char* keyboard_data() {
    return &keyboard.data;
}
