#ifndef GENERAL_H
#define GENERAL_H

#include "ASM_FUNC.H"

int SCREEN_WEIGHT = 320;
int SCREEN_HEIGHT = 200;

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

#define BYTE(addr) ((volatile uint8_t *)(addr))
#define WORD(addr) ((volatile uint16_t *)(addr))
#define DWORD(addr) ((volatile uint32_t *)(addr))

#endif  // GENERAL_H
