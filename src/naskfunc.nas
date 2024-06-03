; naskfunc
; TAB=4

[FORMAT "WCOFF"]	
[INSTRSET "i486p"]	
[BITS 32]			
[FILE "naskfunc.nas"]

		GLOBAL	_io_hlt, _io_cli, _io_sti, _io_stihlt
		GLOBAL	_io_in_BYTE, _io_in_WORD, _io_in_DWORD
		GLOBAL	_io_out_BYTE, _io_out_WORD, _io_out_DWORD
		GLOBAL	_io_load_eflags, _io_store_eflags
		GLOBAL	_load_gdtr, _load_idtr
		
		GLOBAL	_asm_inthandler21, _asm_inthandler27, _asm_inthandler2c
		EXTERN	_inthandler21, _inthandler27, _inthandler2c


; functions

[SECTION .text]

_io_hlt:						; void io_hlt(void);
		HLT
		RET

_io_cli:						; void io_hlt(void);
		CLI
		RET

_io_in_BYTE:	; int io_in8(int port);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,0
		IN		AL,DX
		RET

_io_in_WORD:	; int io_in16(int port);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,0
		IN		AX,DX
		RET

_io_in_DWORD:	; int io_in32(int port);
		MOV		EDX,[ESP+4]		; port
		IN		EAX,DX
		RET

_io_out_BYTE:	; void io_out8(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		AL,[ESP+8]		; data
		OUT		DX,AL
		RET

_io_out_WORD:	; void io_out16(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,[ESP+8]		; data
		OUT		DX,AX
		RET

_io_out_DWORD:	; void io_out32(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,[ESP+8]		; data
		OUT		DX,EAX
		RET

_io_load_eflags:				; int io_load_eflags(void);
		PUSHFD		; PUSH EFLAGS
		POP		EAX
		RET

_io_store_eflags:				; void io_store_eflags(int eflags);
		MOV		EAX,[ESP+4]
		PUSH 	EAX
		POPFD 		; POP EFLAGS
		RET

_load_gdtr:		; void load_gdtr(int limit, int addr);
		MOV		AX,[ESP+4]		; limit
		MOV		[ESP+6],AX
		LGDT	[ESP+6]
		RET

_load_idtr:		; void load_idtr(int limit, int addr);
		MOV		AX,[ESP+4]		; limit
		MOV		[ESP+6],AX
		LIDT	[ESP+6]
		RET

