#include "./H/terminal.h"
#include "./H/display.h"
#include "./H/bootinfo.h"
#include "./H/windows.h"
#include "./H/memory.h"
#include "H/io.h"

struct TERMINAL *terminal_stdout;
struct TERMINAL *terminal_stderr;

//? TEST ONLY

struct TERMINAL *_init_terminal(unsigned char _bg_color, unsigned char _font_color,
					int x0	  , int y0	  ,
					int _xsize, int _ysize,
					int _skipl, int _skipw) {
	TERMINAL *ret = (TERMINAL *) malloc(sizeof (TERMINAL));
	ret->buff = (unsigned char *)malloc(_xsize * _ysize * sizeof(unsigned char));
	ret->window = new_layer(x0, y0, ret->buff, _xsize, _ysize);

	ret->bg_color = _bg_color;
	ret->font_color = _font_color;

	ret->x0 = x0;
	ret->y0 = y0;

	ret->xsize = _xsize;
	ret->ysize = _ysize;
	ret->skip_line = _skipl;
	ret->skip_word = _skipw;

	ret->xlim = ret->xsize / (FONT_WEIGHT + ret->skip_line);
	ret->ylim = ret->ysize / (FONT_HEIGHT + ret->skip_word);
	
	ret->crusor_x = 0;
	ret->crusor_y = 0;
	clear_page(ret);
	return ret;
}

void init_terminals() {
	terminal_stderr = _init_terminal(dark_blue, white, 600, 350, 200, 360, 2, 1);
	terminal_stdout =  _init_terminal(dark_blue, white, 50, 350, 480, 360, 2, 1);
}

#define TAB_LENGTH 4

void print(struct TERMINAL *terminal, char c) {
	int x0 = terminal->crusor_x * (FONT_WEIGHT + terminal->skip_line),
	    y0 = terminal->crusor_y * (FONT_HEIGHT + terminal->skip_word);
	switch (c) {
		case '\n':
			newline(terminal);
			break;
		case '\t':
            do {
                print_char(terminal->buff, 
						   terminal->font_color, terminal->xsize,
                           x0, y0,' ');
				windows_refresh_partial(WINDOWS, terminal->x0 + x0, terminal->y0 + y0, terminal->x0 + x0 + 16, terminal->y0 + y0 + 16);
                crusor_next(terminal);
            } while (terminal->crusor_x % TAB_LENGTH != 0);
			break;
		default:
            print_char(terminal->buff,
					   terminal->font_color, terminal->xsize,
                           x0, y0, c);
			windows_refresh_partial(WINDOWS, terminal->x0 + x0, terminal->y0 + y0, terminal->x0 + x0 + 16, terminal->y0 + y0 + 16);
            crusor_next(terminal);
			break;
	}
}

void clear_page(struct TERMINAL *terminal) {
	int i, size = terminal->xsize * terminal->ysize;
	for (i = 0; i < size; i++) {
		terminal->buff[i] = terminal->bg_color;
	}
	windows_refresh_partial(WINDOWS, terminal->x0, terminal->y0,
	 terminal->x0 + terminal->xsize, terminal->y0 + terminal->ysize);

}

void newline(struct TERMINAL *terminal) {
	terminal->crusor_x = 0;
	terminal->crusor_y ++;
	if (terminal->crusor_y == terminal->ylim) {
		terminal->crusor_y = 0;
		clear_page(terminal);
	}
}

void crusor_next(struct TERMINAL *terminal) {
	terminal->crusor_x ++;
	if (terminal->crusor_x == terminal->xlim) {
		terminal->crusor_x = 0;
		terminal->crusor_y ++;
		if (terminal->crusor_y == terminal->ylim) {
			terminal->crusor_y = 0;
			clear_page(terminal);
		}
	}
}
