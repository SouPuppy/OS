#include "./H/common.h"
#include "H/display.h"
#include "H/io.h"
#include "H/memory.h"
#include "H/windows.h"

#include "./H/frame.h"

Widget* new_widget(Frame *frame, int x, int y, int xsize, int ysize) {
    Widget* ret = (struct Widget *)malloc(sizeof(Widget));
    // mem_debug();
    ret->buff = (unsigned char *)malloc(sizeof(unsigned char) * xsize * ysize);
    // _fprintf(stderr, "size: %d\n", xsize * ysize);
    ret->x = x;
    ret->y = y;
    ret->xsize = xsize;
    ret->ysize = ysize;
    ret->layer = 
        new_layer(
        frame->x0 + ret->x,
        frame->y0 + ret->y,
        ret->buff, 
        ret->xsize,
        ret->ysize);
    _fprintf(stderr, "FX %d   WX %d\n", frame->x0, ret->x);
    return ret;
}

void REFRESH_WIDGET(Frame *frame, Widget *widget) {
    windows_refresh_partial(WINDOWS, frame->x0 + widget->x, frame->y0 + widget->y, frame->x0 + widget->x + widget->xsize, frame->y0 + widget->y + widget->ysize);
}

void init_Frame(Frame *frame, int x0, int y0, int xsize, int ysize) {
    //* Init Frame
    Array_init(Widget*, &frame->widgets);
    frame->x0 = x0;
    frame->y0 = y0;
    frame->xsize = xsize;
    frame->ysize = ysize;

    //* Init first Widget (Background)
    struct Widget *first_widget = new_widget(frame, 0, 0, xsize, ysize);
    Array_append(Widget*, &frame->widgets, first_widget);

    //!!! OVER FLOW !!!!!!!!!!!!!!!!!!!!
    box(first_widget->buff, aquamarine, frame->xsize, 0, 0, frame->xsize, frame->ysize); 
    
    
    // memset(first_widget->buff, aquamarine, first_widget->xsize * first_widget->ysize);

    REFRESH_WIDGET(frame, first_widget);

    first_widget->level = 0;

    frame->layer_level = first_widget->layer->level;    
}





//* init widget
void INIT_WIDGET(Frame *frame, Widget *widget) {
    //TODO check for boundaries
    widget->level = Array_size(&frame->widgets) - 1;
    layer_elevation(WINDOWS, widget->layer, frame->layer_level + widget->level);
}

/* 
 *
 *
 * WIDGETS
 *
 *
*/

//* textbox

void INIT_WIDGET_TEXTBOX(Frame *frame, Widget *widget) {
    INIT_WIDGET(frame, widget);

    memset(widget->buff, white, widget->xsize * widget->ysize);
    widget->string = (char *)malloc(10 * sizeof(char));
    widget->string = "TEXT BOX";
    int i = 0;
    for (i = 0; i < widget->string[i] != '\0'; i++) {
        print_char(widget->buff, black, widget->xsize, 2 + (8 + 1) * i, 2, widget->string[i]);
    }

    REFRESH_WIDGET(frame, widget);
}

void ADD_WIDGET_TEXTBOX(Frame *frame,int x, int y, int xsize, int ysize) {
    struct Widget *widget = new_widget(frame, x, y, xsize, ysize);
    Array_append(Widget*, &frame->widgets, widget);
    INIT_WIDGET_TEXTBOX(frame, widget);
}










void frame_dubug(Frame *frame) {
    int i = 0;
    _fprintf(stdout, "\n\t\t\tLayer Level: %d\n", frame->layer_level);
    for (i = 0; i < Array_size(&frame->widgets); i++) {
        _fprintf(stdout, "level %d | \t level in frame %d\n", Array_value(Widget*, &frame->widgets, i)->layer->level, Array_value(Widget*, &frame->widgets, i)->level);
    }
}