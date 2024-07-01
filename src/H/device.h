#ifndef device_h
#define device_h

typedef struct MOUSE_DET {
    unsigned char buf[3], phase;
    int x, y;
    int btn; // 001 'L', 010 'R', 100 'C'
} MOUSE_DET;

typedef struct KEYBOARD_DET {
    unsigned char data;
} KEYBOARD_DET;

extern struct MOUSE_DET    *ms_det;
extern struct KEYBOARD_DET *kb_det;

void init_mouse_detect();
void init_keyboard_detect();

int detect_mouse(struct MOUSE_DET *mouse);
int detect_keyboard();
// unsigned char* mouse_data_buf();
// unsigned char* keyboard_data();


typedef struct MOUSE {
    int x, y;
    int xlim, ylim;
} MOUSE;

extern struct MOUSE mouse;

void init_mouse();

#endif  // device_h
