#ifndef frame_h
#define frame_h

#include "common.h"
#include "windows.h"

typedef struct Widget {

} Widget;

typedef struct Frame {
    int x0, y0, x1, y1;
    Array   values;
} Frame;

#endif