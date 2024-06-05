#include "./H/common.h"
#include "./H/bootinfo.h"
#include "./H/display.h"
#include "./H/io.h"
#include "./H/terminal.h"

extern struct BOOTINFO *boot_info;

FILE *stdin;
FILE *stdout;
FILE *stderr;

FILE _stdin  = (FILE){ 0, NULL, 0, 0 };
FILE _stdout = (FILE){ 1, NULL, 0, 0 };
FILE _stderr = (FILE){ 2, NULL, 0, 0 };

void init_io(void) {
    stdin  = &_stdin;
    stdout = &_stdout;
    stderr = &_stderr;
}

int line_spacing = 2;
int word_spacing = 1;

int _write(FILE *stream, char c) {
    if (stream->_file == 1) { // stdout
        print(main_terminal, c);
        return 1;
    }
    return -1;
}

void itoa(int num, char *str) {
    int i = 0, j = 0;
    int isNegative = 0;
  
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

int _fprintf(FILE *stream, const char *format, ...) {
    char **arg = (char **)&format;
    arg++;

    const char *p = format;
    int count = 0;
    while (*p) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 'c': {
                    char c = *(char *)arg++;
                    _write(stream, c);
                    count++;
                    break;
                }
                case 's': {
                    const char *s = *(char **)arg++;
                    while (*s) {
                        _write(stream, *s++);
                        count++;
                    }
                    break;
                }
                case 'd': {
                    int num = *(int *)arg++;
                    char buf[32];
                    char *bp;
                    itoa(num, buf);
                    for (bp = buf; *bp; bp++) {
                        _write(stream, *bp);
                        count++;
                    }
                    break;
                }
            }
        }
        else if (*p == '\\') {
            p++;
            switch(*p) {
                case 'n':
                    _write(stream, '\n');
                    break;
                case 't':
                    _write(stream, '\t');
                    break;
                case '\\':
                    _write(stream, '\\');
                    break;
                default:
                    _write(stream, '\\');
                    _write(stream, *p);
                    break;
            }
        } else {
            _write(stream, *p);
            count++;
        }
        p++;
    }

    return count;
    return 1;
}
