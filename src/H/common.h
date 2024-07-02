#ifndef GENERAL_H
#define GENERAL_H

// ----- asm functions -----

void io_hlt(void);
void io_cli(void);
void io_sti(void);
void io_stihlt(void);

int io_in8 (int port);
int io_in16(int port);
int io_in32(int port);

void io_out8 (int port, int data);
void io_out16(int port, int data);
void io_out32(int port, int data);

int  io_load_eflags(void);
void io_store_eflags(int eflags);
void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);
int  load_cr0(void);
void store_cr0(int cr0);
unsigned int memtest_sub(unsigned int start, unsigned int end);

void asm_inthandler21(void);
void asm_inthandler27(void);
void asm_inthandler2c(void);

// ----- type define -----

#define  uint8_t    unsigned char
#define  uint16_t   unsigned short
#define  uint32_t   unsigned int
#define  size_t     unsigned int

#define NULL ((void*)0)

// ----- other functions ----- 

#define BYTE(addr) ((uint8_t *)(addr))
#define WORD(addr) ((uint16_t *)(addr))
#define DWORD(addr) ((uint32_t *)(addr))

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a < b ? b : a)

#endif  // GENERAL_H
