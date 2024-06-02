#ifndef GENERAL_H
#define GENERAL_H


// ----- 16x colors -----

#define true_Red        0
#define scarlet         1
#define rose            2
#define tangerine       3
#define amber           4
#define willow          5
#define green           6
#define aquamarine      7
#define dark_Teal       8
#define azure           9
#define dark_Blue       10
#define iris            11
#define white           12
#define skin            13
#define withered_Tea    14
#define black           15

#define NULL ((void*)0)

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

#define BYTE(addr) ((uint8_t *)(addr))
#define WORD(addr) ((uint16_t *)(addr))
#define DWORD(addr) ((uint32_t *)(addr))

#endif  // GENERAL_H
