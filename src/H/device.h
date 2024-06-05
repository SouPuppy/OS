#ifndef device_h
#define device_h

typedef struct MOUSE {
    unsigned char buf[3], phase;
    int x, y, btn;
};

typedef struct KEYBOARD {
    unsigned char data;
};

extern struct MOUSE mouse;
extern struct KEYBOARD keyboard;

void init_mouse();
int detect_mouse();
unsigned char* mouse_data_buf();

void init_keyboard();
int detect_keyboard();
unsigned char* keyboard_data();

#endif  // device_h
