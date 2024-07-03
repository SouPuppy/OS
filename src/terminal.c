#include "./H/terminal.h"
#include "./H/display.h"
#include "./H/bootinfo.h"
#include "./H/windows.h"
#include "./H/memory.h"
#include "H/io.h"

struct TERMINAL *main_terminal;

//? TEST ONLY
//! FAILED TO LOAD 2nd terminal
//// struct TERMINAL *second_terminal;

void init_main_terminal() {
	init_terminal(main_terminal, dark_blue, white, 200, 200, 480, 360, 2, 1);
	//// init_terminal(second_terminal, iris, white, 10, 10, 150, 300, 2, 1);
}

void init_terminal(struct TERMINAL *terminal,
					unsigned char _bg_color, unsigned char _font_color,
					int x0	  , int y0	  ,
					int _xsize, int _ysize,
					int _skipl, int _skipw) {
	// buff = allocate(xlim * ylim, char)
	// terminal = malloc(sizeof (struct TERMINAL));

	terminal->bg_color = _bg_color;
	terminal->font_color = _font_color;

	terminal->x0 = x0;
	terminal->y0 = y0;

	terminal->xsize = _xsize;
	terminal->ysize = _ysize;
	terminal->skip_line = _skipl;
	terminal->skip_word = _skipw;

	terminal->xlim = terminal->xsize / (FONT_WEIGHT + terminal->skip_line);
	terminal->ylim = terminal->ysize / (FONT_HEIGHT + terminal->skip_word);
	
	terminal->crusor_x = 0;
	terminal->crusor_y = 0;

	terminal->buff = malloc(terminal->xsize * terminal->ysize * sizeof (unsigned char));
	clear_page(terminal);

	terminal->window = new_layer(terminal->x0, terminal->y0, terminal->buff, terminal->xsize, terminal->ysize);
}

#define TAB_LENGTH 4

void print(struct TERMINAL *terminal, char c) {
	switch (c) {
		case '\n':
			newline(terminal);
			break;
		case '\t':
            do {
                print_char(terminal->buff, 
						   terminal->font_color, terminal->xsize,
                           terminal->crusor_x * (FONT_WEIGHT + terminal->skip_line),
                           terminal->crusor_y * (FONT_HEIGHT + terminal->skip_word),
                           ' ');
                crusor_next(terminal);
            } while (terminal->crusor_x % TAB_LENGTH != 0);
			break;
		default:
            print_char(terminal->buff,
					   terminal->font_color, terminal->xsize,
                       terminal->crusor_x * (FONT_WEIGHT + terminal->skip_line),
                       terminal->crusor_y * (FONT_HEIGHT + terminal->skip_word),
                       c);
            crusor_next(terminal);
			break;
	}
}

void clear_page(struct TERMINAL *terminal) {
	int i, size = terminal->xsize * terminal->ysize;
	for (i = 0; i < size; i++) {
		terminal->buff[i] = terminal->bg_color;
	}
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