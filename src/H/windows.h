#ifndef windows_h
#define windows_h

#define LAYER_UNUSED    0
#define LAYER_USED      1

#define LAYER_HIDE     -1

typedef struct Layer {
    unsigned char *buff;
    int weight, height;
    int x, y;
    int col_inv; // color invisible
    int level;
    int flag;
} Layer, Window;

#define MAX_LAYERS  256

typedef struct Windows {
    unsigned char *vram;
    int weight, height, top;
    struct Layer * ordered_layers[MAX_LAYERS];
    struct Layer unordered_layers[MAX_LAYERS];
} Windows;

extern struct Windows *WINDOWS;

extern struct Layer   *LAYER_BACKGROUND;
extern struct Layer   *LAYER_CRUSOR;
extern unsigned char  *LAYER_BUFF_BACKGROUND;
extern unsigned char   LAYER_BUFF_CRUSOR[256];


#include "memory.h"

void init_crusor();
void init_mouse_cursor(char *mouse, char back_color);
void init_windows();
struct Windows  *windows_init(struct MEMMAN *man, unsigned char *vram, int xsize, int ysize);
struct Layer *layer_alloc(struct Windows *windows);
void          layer_setbuff(struct Layer *layer, unsigned char *buff, int weight, int height, int col_inv);
void          layer_elevation(struct Windows *windows, struct Layer *layer, int level);
void          windows_refresh(struct Windows *windows);
void          layer_slide(struct Windows *windows, struct Layer *layer, int new_x, int new_y);
void          layer_free(struct Windows *windows, struct Layer *layer);
void          update_crusor_position(int det_x, int det_y);
void          display_crusor();

// APP FUNC
struct Layer *new_layer(int x0, int y0, unsigned char *buff, int weight, int height);

#endif
