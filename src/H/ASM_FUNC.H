#ifndef ASM_FUNC_H
#define ASM_FUNC_H

void io_hlt(void);
void io_cli(void);

int  io_load_eflags(void);
void io_store_eflags(int eflags);

// write in hardware
void io_out_BYTE(int port, int data);
void io_out_WORD(int port, int data);
void io_out_DWORD(int port, int data);

#endif  // ASM_FUNC_H
