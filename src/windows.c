#include "./H/common.h"
#include "./H/windows.h"
#include "./H/memory.h"
#include "H/io.h"

struct Windows *WINDOWS;

struct Layer   *LAYER_BACKGROUND;
struct Layer   *LAYER_CRUSOR;
unsigned char  *LAYER_BUFF_BACKGROUND;
unsigned char   LAYER_BUFF_CRUSOR[256];

#include "./H/bootinfo.h"
#include "./H/display.h"

#define BACK_COLOR dark_teal
#define COLOR_INVISIBLE 99

int crusor_x, crusor_y;

void init_crusor() {
    // preparing buff
    init_mouse_cursor(LAYER_BUFF_CRUSOR, COLOR_INVISIBLE);
    crusor_x = boot_info->scrnx / 2;
    crusor_y = boot_info->scrny / 2;

    // applying for a new layer
    LAYER_CRUSOR = layer_alloc(WINDOWS);

    // init layer
    layer_setbuff(LAYER_CRUSOR, LAYER_BUFF_CRUSOR, 16, 16,  COLOR_INVISIBLE);
    layer_slide(WINDOWS, LAYER_CRUSOR, crusor_x, crusor_y);
    layer_elevation(WINDOWS, LAYER_CRUSOR, 1);
}

void init_mouse_cursor(char *mouse, char back_color) {
	static char cursor[16][16] = {
		 "**************..",
		 "*OOOOOOOOOOO*...",
		 "*OOOOOOOOOO*....",
		 "*OOOOOOOOO*.....",
		 "*OOOOOOOO*......",
		 "*OOOOOOO*.......",
		 "*OOOOOOO*.......",
		 "*OOOOOOOO*......",
		 "*OOOO**OOO*.....",
		 "*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	int x, y;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			if (cursor[y][x] == '*') {
				mouse[y * 16 + x] = black;
			}
			if (cursor[y][x] == 'O') {
				mouse[y * 16 + x] = white;
			}
			if (cursor[y][x] == '.') {
				mouse[y * 16 + x] = back_color;
			}
		}
	}
	return;
}

void init_background() {
    // preparing buff
    LAYER_BUFF_BACKGROUND = (unsigned char *) memman_alloc_4k(mem_man, boot_info->scrnx * boot_info->scrny);
    box(LAYER_BUFF_BACKGROUND, BACK_COLOR, boot_info->scrnx, 0, 0, boot_info->scrnx, boot_info->scrny);

    // applying for a new layer
    LAYER_BACKGROUND = layer_alloc(WINDOWS);

    // init layer
    layer_setbuff(LAYER_BACKGROUND, LAYER_BUFF_BACKGROUND, boot_info->scrnx, boot_info->scrny,  -1);
    layer_slide(WINDOWS, LAYER_BACKGROUND, 0, 0);
    layer_elevation(WINDOWS, LAYER_BACKGROUND, 0);
}

void init_windows() {
    WINDOWS = windows_init(mem_man, boot_info->vram, boot_info->scrnx, boot_info->scrny);
    init_background();
    init_crusor();
    windows_refresh(WINDOWS);
}

struct Windows *windows_init(struct MEMMAN *man, unsigned char *vram, int xsize, int ysize) {
    struct Windows *windows;

    int i;
    windows = (struct Windows *) memman_alloc_4k(man, sizeof (struct Windows));
    if (windows == 0) {
        goto err;
    }
    windows->vram   = vram;
    windows->width = xsize;
    windows->height = ysize;
    windows->top    = -1;
    for (i = 0; i < MAX_LAYERS; i++) {
        windows->unordered_layers[i].flag = LAYER_UNUSED;
    }
err:
    return windows;
}

struct Layer *layer_alloc(struct Windows *windows) {
    struct Layer *layer;
    int i;
    for (i = 0; i < MAX_LAYERS; i++) {
        if (windows->unordered_layers[i].flag == LAYER_UNUSED) {
            layer = &windows->unordered_layers[i];
            layer->flag  = LAYER_USED;
            layer->level = LAYER_HIDE;
            return layer;
        }
    }
    return 0;
}

void layer_setbuff(struct Layer *layer, unsigned char *buff, int width, int height, int col_inv) {
    layer->buff     = buff;
    layer->width   = width;
    layer->height   = height;
    layer->col_inv  = col_inv;
    return ;
}

void layer_elevation(struct Windows *windows, struct Layer *layer, int level) {
    int i, old_level = layer->level;

    if (level == old_level) return ;
    if (level > windows->top + 1)  level = windows->top + 1;
    if (level < -1)     level = -1;
    
    layer->level = level;

    if (level < old_level) {
        if (level > -1) {
            for (i = old_level; i > level; i--) {
                windows->ordered_layers[i] = windows->ordered_layers[i - 1];
                windows->ordered_layers[i]->level = i;
            }
            windows->ordered_layers[level] = layer;
        }
        // HIDE THIS LAYER
        else {
            if (old_level != windows->top) {
                for (i = old_level; i < windows->top; i++) {
                    windows->ordered_layers[i] = windows->ordered_layers[i + 1];
                    windows->ordered_layers[i]->level = i;
                }
            }
            windows->top--;
        }
    }

    else {
        if (old_level > -1) {
            for (i = old_level; i < level; i++) {
                windows->ordered_layers[i] = windows->ordered_layers[i + 1];
                windows->ordered_layers[i]->level = i;
            }
            windows->ordered_layers[level] = layer;
        }
        else {
            for (i = windows->top; i >= level; i--) {
                windows->ordered_layers[i + 1] = windows->ordered_layers[i];
                windows->ordered_layers[i + 1]->level = i + 1;
            }
            windows->top ++;
            windows->ordered_layers[level] = layer;
        }
    }
    windows_refresh(windows);
    return ;
}

void windows_refresh(struct Windows *windows) {
    int i, bx, by, x, y; // bias_y, y,
    unsigned char *buff, data, *vram = windows->vram;
    struct Layer *layer;
    for (i = 0; i <= windows->top; i++) {
        layer = windows->ordered_layers[i];
        buff  = layer->buff;
        for (by = 0; by < layer->height; by++) {
            y = layer->y + by; // can optimize by deleting y;
            for (bx = 0; bx < layer->width; bx++) {
                x = layer->x + bx;
                // position in layer    : by * layer->width + bx
                // position in windows  : y * windows->width + x
                data = buff[by * layer->width + bx];
                if (data != layer->col_inv) {
                    vram[y * windows->width + x] = data;
                }
            }
        } 
    }
    return ;
}

void windows_refresh_partial(struct Windows *windows, int x0, int y0, int x1, int y1) {
    int i, ix, iy, bx, by;
    int y_min, y_max, x_min, x_max;
    unsigned char *buff, data, *vram = windows->vram;
    struct Layer *layer;
    for (i = 0; i <= windows->top; i++) {
        layer = windows->ordered_layers[i];
        buff  = layer->buff;
        x_min = max(x0, layer->x);
        x_max = min(x1, layer->x + layer->width);
        y_min = max(y0, layer->y);
        y_max = min(y1, layer->y + layer->height);

        // _fprintf("[%d, %d] [%d, %d]   [%d, %d] [%d, %d]   |   [%d, %d] [%d, %d]\n", 
        // &x0, &y0, &x1, &y1, 
        // &layer->x, &layer->y, &layer->x + layer->width, &layer->y + layer->height,
        // &x_min, &y_min, &x_max, &y_max
        // );

        for (iy = y_min, by = y_min - layer->y; iy < y_max; by++, iy++) {
            for (ix = x_min, bx = x_min - layer->x; ix < x_max; bx++, ix++) {
                data = buff[by * layer->width + bx];
                if (data != layer->col_inv) {
                    vram[iy * windows->width + ix] = data;
                }
            }
        }
    }
    return ;
}

void layer_slide(struct Windows *windows, struct Layer *layer, int new_x, int new_y) {
    int old_x = layer->x, old_y = layer->y;
    layer->x = new_x;
    layer->y = new_y;
    if (layer->level >= 0) { // On Dislplay
        windows_refresh_partial(windows, old_x, old_y, old_x + layer->width, old_y + layer->height);
        windows_refresh_partial(windows, layer->x, layer->y, layer->x + layer->width, layer->y + layer->height);
    }
    return ;
}

void layer_free(struct Windows *windows, struct Layer *layer) {
    if (layer->level >= 0) { // On Dislplay
        layer_elevation(windows, layer, LAYER_HIDE);
    }
    layer->flag = LAYER_UNUSED;
    return ;
}

void update_crusor_position(int det_x, int det_y) {
    crusor_x += det_x;
    crusor_y += det_y;
    if (crusor_x <= 0) crusor_x = 0;
    if (crusor_y <= 0) crusor_y = 0;
    if (crusor_x> boot_info->scrnx - 16 ) crusor_x = boot_info->scrnx - 16;
    if (crusor_y> boot_info->scrny - 16 ) crusor_y = boot_info->scrny - 16;
    layer_slide(WINDOWS, LAYER_CRUSOR, crusor_x, crusor_y);
    return ;
}

// Should Check for boundary
struct Layer *new_layer(int x0, int y0, unsigned char *buff, int width, int height) {
    int new_layer_level = LAYER_CRUSOR->level;
    struct Layer *ret = layer_alloc(WINDOWS);
    layer_setbuff(ret, buff, width, height, 99);
    layer_slide(WINDOWS, ret, x0, y0);
    layer_elevation(WINDOWS, ret, new_layer_level);
    // refresh
    ///
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    return ret;
}
