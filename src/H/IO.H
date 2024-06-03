#ifndef IO_H
#define IO_H

#include "common.h"

typedef struct _iobuf {
    int _file;       // file descriptor
    char *_ptr;
    char _buff;
    int _buff_size;
} FILE;


void init_io(void);
void print_char(unsigned char color, int x, int y, char c);
int _write(FILE *stream, char c);
void itoa(int num, char *str);
int _fprintf(FILE *stream, const char *format, ...);

#endif // IO_H
