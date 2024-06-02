#ifndef IO_H
#define IO_H

typedef struct _iobuf {
    int _file;       // file descriptor
    char *_ptr;
    char _buff;
    int _buff_size;
} FILE;


void init_IO();
void print_char(unsigned char color, int x, int y, char c);
// int fprintf(FILE *stream, const char *format, ...);
int _write(FILE *stream, char c);

#endif // IO_H
