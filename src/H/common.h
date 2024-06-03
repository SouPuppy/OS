#ifndef GENERAL_H
#define GENERAL_H

// ----- asm functions -----

void io_hlt(void);
void io_cli(void);

void io_in_BYTE (int port, int data);
void io_in_WORD (int port, int data);
void io_in_DWORD(int port, int data);

void io_out_BYTE (int port, int data);
void io_out_WORD (int port, int data);
void io_out_DWORD(int port, int data);

int  io_load_eflags(void);
void io_store_eflags(int eflags);

void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);

#define NULL ((void*)0)

// ----- type define -----

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

// ----- other functions ----- 

#define BYTE(addr) ((uint8_t *)(addr))
#define WORD(addr) ((uint16_t *)(addr))
#define DWORD(addr) ((uint32_t *)(addr))

#endif  // GENERAL_H
