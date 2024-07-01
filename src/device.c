#include "./H/common.h"
#include "./H/device.h"
#include "./H/pic.h"

#include "./H/bootinfo.h"
#include "./H/display.h"


struct MOUSE_DET    mouse_data_buf;
struct KEYBOARD_DET keyboard_data_buf;

struct MOUSE_DET    *ms_det;
struct KEYBOARD_DET *kb_det;

void init_mouse_detect() {
    ms_det = &mouse_data_buf;
    ms_det->phase = 0;
}

void init_keyboard_detect() {
    kb_det = &keyboard_data_buf;
}

int detect_mouse(struct MOUSE_DET *mouse) {
    if (fifo_count(&mousefifo) == 0) return -1;
    int data = fifo_deq(&mousefifo);
    io_sti();
    switch (mouse->phase) {
		case 0 :
			if (data == 0xfa) {
				mouse->phase = 1;
			}
			break;
		case 1 :
			mouse->buf[0] = data;
			mouse->phase = 2;
			break;
		case 2 :
			mouse->buf[1] = data;
			mouse->phase = 3;
			break;
		case 3 :
			mouse->buf[2] = data;
			mouse->phase = 1;

            mouse->btn = mouse->buf[0] & 0x07;
            mouse->x   = mouse->buf[1];
            mouse->y   = mouse->buf[2];
            if ((mouse->buf[0] & 0x10) != 0) {
                mouse->x |= 0xffffff00;
            }
            if ((mouse->buf[0] & 0x20) != 0) {
                mouse->y |= 0xffffff00;
            }
            mouse->y = -mouse->y;
			break;
	}
    return mouse->phase;
}

int detect_keyboard(struct KEYBOARD_DET *keyboard) {
    if (fifo_count(&keyfifo) == 0) return -1;
    int data = fifo_deq(&keyfifo);
    io_sti();
    keyboard->data = data;
    return 1;
}








struct MOUSE mouse;

void init_mouse() {
    mouse.xlim = boot_info->scrnx;
    mouse.ylim = boot_info->scrny;
    mouse.x = mouse.xlim / 2;
    mouse.y = mouse.ylim / 2;
}

// void display_mouse() {
//     box(white, mouse.x, mouse.y, mouse.x + 8, mouse.y + 16);
// }

void mouse_update(int det_x, int det_y) {
    mouse.x = mouse.x + det_x;
    mouse.y = mouse.y + det_y;
}