#ifndef frame_h
#define frame_h

#include "common.h"
#include "memory.h"
#include "windows.h"

#define WIDGET_TEXTBOX  1
#define WIDGET_BUTTON   2

typedef struct Widget {
    int x, y, xsize, ysize;
    int widget_type;
    unsigned char *buff;
    Layer *layer;
    int level;
//* data
//? Pixels
//? TEXTBOX:
    char *string;

    /*
    * refresh()         // reffresh this widget
    * handle_event()
    */
} Widget;

typedef struct Frame {
    int     x0, y0, xsize, ysize;
    Array   widgets;
    int layer_level;
    // Methods
    /*
    * refresh_all()         // reffresh all widgets
    * add_widget()
    */
} Frame;

void init_Frame(Frame *frame, int x0, int y0, int xsize, int ysize);
void INIT_WIDGET(Frame *frame, Widget *widget);
void REFRESH_WIDGET(Frame *frame, Widget *widget);

void INIT_WIDGET_TEXTBOX(Frame *frame, Widget *widget);
void ADD_WIDGET_TEXTBOX(Frame *frame,int x, int y, int xsize, int ysize);


void frame_dubug(Frame *frame);

#endif
