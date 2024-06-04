#ifndef TERMINAL_H
#define TERMINAL_H

#include "common.h"

typedef struct TERMINAL {
	unsigned char bg_color, font_color;
	int xsize, ysize;
    int xlim, ylim; // by_char
    int crusor_x, crusor_y;
	int mouse_x, mouse_y;
	int skip_line, skip_word;
    // char *buff;
};

extern struct TERMINAL *main_terminal;

void init_main_terminal();
void init_terminal(struct TERMINAL *terminal,
					unsigned char _bg_color, unsigned char _font_color,
					int _xsize, int _ysize,
					int _skipl, int _skipw);
void print(struct TERMINAL *terminal, char c);
void refresh_page(struct TERMINAL *terminal);
void crusor_next(struct TERMINAL *terminal);

#endif  // TERMINAL_H
