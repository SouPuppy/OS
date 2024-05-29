#ifndef GENERAL_H
#define GENERAL_H

// ----- type define -----

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

// ----- asm functions -----

void io_hlt(void);
void io_cli(void);

int  io_load_eflags(void);
void io_store_eflags(int eflags);

// write in hardware
void io_out_BYTE (int port, int data);
void io_out_WORD (int port, int data);
void io_out_DWORD(int port, int data);


// ----- other functions ----- 

#define BYTE(addr) ((volatile uint8_t *)(addr))
#define WORD(addr) ((volatile uint16_t *)(addr))
#define DWORD(addr) ((volatile uint32_t *)(addr))

#endif  // GENERAL_H
