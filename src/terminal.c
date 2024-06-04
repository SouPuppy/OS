#include "./H/terminal.h"
#include "./H/display.h"
#include "./H/bootinfo.h"

struct TERMINAL *main_terminal;
// // #define px *1

#define FONT_HEIGHT 16
#define FONT_WEIGHT 8

void init_main_terminal() {
	init_terminal(main_terminal, black, white, boot_info->scrnx, boot_info->scrny, 2, 1);
	clear_page(main_terminal);
}

void init_terminal(struct TERMINAL *terminal,
					unsigned char _bg_color, unsigned char _font_color,
					int _xsize, int _ysize,
					int _skipl, int _skipw) {
	// buff = allocate(xlim * ylim, char)
	terminal->bg_color = _bg_color;
	terminal->font_color = _font_color;

	terminal->xsize = _xsize;
	terminal->ysize = _ysize;
	terminal->skip_line = _skipl;
	terminal->skip_word = _skipw;

	terminal->xlim = terminal->xsize / (FONT_WEIGHT + terminal->skip_line);
	terminal->ylim = terminal->ysize / (FONT_HEIGHT + terminal->skip_word);
	
	terminal->crusor_x = 0;
	terminal->crusor_y = 0;
}

#define TAB_LENGTH 4

void print(struct TERMINAL *terminal, char c) {
	switch (c) {
		case '\n':
			newline(terminal);
			break;
		case '\t':
            do {
                print_char(terminal->font_color,
                           terminal->crusor_x * (FONT_WEIGHT + terminal->skip_line),
                           terminal->crusor_y * (FONT_HEIGHT + terminal->skip_word),
                           ' ');
                crusor_next(terminal);
            } while (terminal->crusor_x % TAB_LENGTH != 0);
			break;
		default:
            print_char(terminal->font_color,
                       terminal->crusor_x * (FONT_WEIGHT + terminal->skip_line),
                       terminal->crusor_y * (FONT_HEIGHT + terminal->skip_word),
                       c);
            crusor_next(terminal);
			break;
	}
}

void clear_page(struct TERMINAL *terminal) {
	box(terminal->bg_color, 0, 0, terminal->xsize, terminal->ysize);
}

void newline(struct TERMINAL *terminal) {
	terminal->crusor_x = 0;
	terminal->crusor_y ++;
	if (terminal->crusor_y == terminal->ylim) {
		terminal->crusor_y = 0;
		clear_page(terminal);
	}
}

// // void clear_word(struct TERMINAL *terminal, int x, int y);
// // void clear_line(struct TERMINAL *terminal, int x);
// // void clear_page(struct TERMINAL *terminal, void);
// // void crusor_set(struct TERMINAL *terminal, int x, int y);

// // void crusor_prev(struct TERMINAL *terminal);
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
// // void crusor_up	(struct TERMINAL *terminal);
// // void crusor_down(struct TERMINAL *terminal);
